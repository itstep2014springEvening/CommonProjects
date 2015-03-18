using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.Distributions;

namespace Events
{
    struct AverageAccumulator<T>
    {
        private uint N;
        private T sum;

        public void Add(T value)
        {
            sum = (dynamic)sum + (dynamic)value;
            N++;
        }
        public void Reset()
        {
            sum = default(T);
            N = 0;
        }
        public T Value
        {
            get
            {
                return ((dynamic)sum) / N;
            }
        }
    }

    class MyMultimap<TKey, TValue> where TKey : IComparable
    {
        SortedDictionary<TKey, List<TValue>> tree = new SortedDictionary<TKey, List<TValue>>();

        public void Add(TKey key, TValue value)
        {

            if (tree.ContainsKey(key) == false)
            {
                tree[key] = new List<TValue>();
            }
            tree[key].Add(value);
        }
        public void RemoveFirst()
        {
            if (tree.First().Value != null)
            {
                tree.First().Value.Remove(tree.First().Value.First());
            }
            if (tree.First().Value.Count == 0)
            {
                tree.Remove(tree.First().Key);
            }
        }
        public TValue First()
        {
            return tree.First().Value.First();
        }
    }
    public enum Day { M, D, Mit, Don, Fr, Sb, S };
    abstract class Event
    {
        public readonly uint time;
        public Event(uint time)
        {
            this.time = time;
        }
        public virtual void process() { }
    }
    class EventQueue : MyMultimap<uint, Event>
    {
        public void Add(Event e)
        {
            base.Add(e.time, e);
        }
    }

    class NewPassangerEvent : Event
    {
        public readonly List<Stop>.Enumerator where;
        public NewPassangerEvent(uint time, List<Stop>.Enumerator where)
            : base(time)
        {
            this.where = where;
        }

        public override void process()
        {
            new Passanger(where);
        }
    }

    class BusArrivalEvent : Event
    {
        Bus bus;
        Passanger passanger;
        public BusArrivalEvent(uint time, Bus bus) :
            base(time)
        {
            this.bus = bus;
        }
        public override void process()
        {
            bus.next();
            Console.WriteLine("{0}: A Bus arrived to the  {1}", Program.time, bus.where.name);
            bus.takeoff();
            bus.boarding();
            Program.avgPassengers.Add(Bus.passangers.Count);
            double mean = bus.where.timeToNext;
            
            double stdDev =mean/4;
            double randomGaussianValue = 0;
            do{
            MathNet.Numerics.Distributions.Normal normalDist = new Normal(mean, stdDev);
            randomGaussianValue = normalDist.Sample();}
            while(randomGaussianValue<2*mean/3);

            Program.events.Add(new BusArrivalEvent(time + (uint)randomGaussianValue, bus));

        }
    }

    class StatisticsEvents : Event
    {
        public StatisticsEvents(uint time):
            base(time)
        {

        }
        public override void process()
        {
            Console.WriteLine(Program.avgPassengers.Value);
            Program.avgPassengers.Reset();
            Program.events.Add(new StatisticsEvents(time + 50));
        }
    }
    class Stop
    {
        public Queue<Passanger> passangers;
       //время прихода автобуса на следующую остановку
        public readonly double timeToNext;
        // интервал прихода пассажиров на данную остановку
        public readonly double passangerInterval;
        public readonly string name;
        public Stop(string name, double timeToNext, double passangerInterval)
        {
            this.name = name;
            this.timeToNext = timeToNext;
            this.passangerInterval = passangerInterval;
            this.passangers = new Queue<Passanger>();
        }
    }
    class Bus
    {
        public List<Stop>.Enumerator stopEnumerator;
        const uint capacity = 18;
        // время выхода на линию
        static uint startTime = 1;
        
        // 
        public static List<Passanger> passangers = new List<Passanger>();
        public Stop where
        {
            get
            {
                return stopEnumerator.Current;
            }
        }

        public Bus()

        {
            this.stopEnumerator = Program.stops.GetEnumerator();
            Program.events.Add(new BusArrivalEvent(startTime, this));
            startTime += Program.intervalTime;
        }
        public void next()
        {
            if (stopEnumerator.MoveNext() == false)
            {
                stopEnumerator = Program.stops.GetEnumerator();
                stopEnumerator.MoveNext();
            }
        }

        public void boarding()
        {
            while ((where.passangers.Count > 0) && (Bus.passangers.Count < Bus.capacity))
            {
                Passanger p = where.passangers.Dequeue();
                passangers.Add(p);
                uint time = Program.time - p.arrival; 
                Console.Write("{0}: Пассажир садится в аватобус  на {1}", Program.time, where.name);
                Console.WriteLine(" , прождав автобус {0} секунд", time);
            }

        }
        public void takeoff()
        {
            passangers.RemoveAll( p => p.exitStop == where);
//                     Console.WriteLine("{0}: Пассажир выходит из аватобуса  на {1}", Program.time, where.name);
           
        }

    }
    class Passanger
    {
        public List<Stop>.Enumerator stopEnumerator;
       
        /*double stdDev = 10;

            double mean = 100;
            MathNet.Numerics.Distributions.Normal normalDist = new Normal(mean, stdDev);
            double randomGaussianValue = normalDist.Sample();
            MathNet.Numerics.Distributions.Exponential expDist = new Exponential(1/mean);
            double randomExpValue = expDist.Sample();
            Console.WriteLine(randomGaussianValue);
            Console.WriteLine(randomExpValue);*/
        
        //время прихода на остановку
       public  readonly uint arrival;
        
        // остановка, где пассажир ожидает
        readonly Stop boardingStop;
        
        //остановка, где выходит
        readonly public Stop exitStop;
        readonly public Stop previousExitStop;

        public Passanger(List<Stop>.Enumerator stopEnumerator)
        {
           
            double randomHumanArrival=-1;
            while(randomHumanArrival<0)
            {
               MathNet.Numerics.Distributions.Exponential expDist = new Exponential(1 /stopEnumerator.Current.passangerInterval);
               randomHumanArrival = expDist.Sample();
            }
            arrival = Program.time;
            uint nextArrival = Program.time +(uint) randomHumanArrival;
            Program.events.Add(new NewPassangerEvent(nextArrival, stopEnumerator));

            ////////////////////////


            this.boardingStop = stopEnumerator.Current;
            this.boardingStop.passangers.Enqueue(this);

            uint numberOfStops;
            double stdDev = 0.5;
            double mean1 = 2;
            do
            {
                MathNet.Numerics.Distributions.Normal normalDist = new Normal(mean1, stdDev);
                numberOfStops = (uint)normalDist.Sample();
            }
            while (numberOfStops < 1);
            Console.WriteLine("{0}: New passanger at {1}, хочет проехать {2} остановки", Program.time, stopEnumerator.Current.name, numberOfStops);


            for (; numberOfStops > 0; numberOfStops--)
            {
                previousExitStop = stopEnumerator.Current;//zavtra edet v null

                if (stopEnumerator.MoveNext() == false)
                {
               
                 break;
                }
                if(stopEnumerator.Current == null)
                {
                    exitStop = previousExitStop;
                }
              /*  if(stopEnumerator.MoveNext() == null)
                {
                    stopEnumerator.MoveNext() = stopEnumerator.Current;
                }*/
            }
            exitStop =previousExitStop;
          

        }
    }

    class Program
    {
        public static uint time;
        public static uint intervalTime;
        public static EventQueue events;
        public static List<Stop> stops;
        public static AverageAccumulator<long> avgPassengers;
        public static AverageAccumulator<int> avgWait;
        public const uint numberOfBuses = 10;
        static void Main(string[] args)
        {
            time = 0;
            stops = new List<Stop>(){
                    new Stop("Kastrychnickaja", 20, 3),// vremya do next ostanovki (200) , interval prihoda passagirov(3)
                    new Stop("Niamiha", 18, 6),
                    new Stop("Frunzenskaja", 19, 5),
                    new Stop("Niamiha", 30, 6)
            };
            foreach(Stop stop in stops)
            {
                intervalTime += (uint)stop.timeToNext;
            }
            intervalTime /= numberOfBuses;
            // добовляем событие прихода первых пассажиров
            List<Stop>.Enumerator stopEnumerator = stops.GetEnumerator();
            events = new EventQueue();
            while (stopEnumerator.MoveNext())
            {
                events.Add(new NewPassangerEvent(1, stopEnumerator));
            }

            for (int i = 0; i < numberOfBuses; i++)
            {
                Bus bus = new Bus();
            }

            events.Add(new StatisticsEvents(50));

            while (time < 300)
            {
      
                time = events.First().time;
                events.First().process();
                events.RemoveFirst();

            }
            
            
  /*          double stdDev = 10;

            double mean = 100;
            MathNet.Numerics.Distributions.Normal normalDist = new Normal(mean, stdDev);
            double randomGaussianValue = normalDist.Sample();
            MathNet.Numerics.Distributions.Exponential expDist = new Exponential(1/mean);
            double randomExpValue = expDist.Sample();
            Console.WriteLine(randomGaussianValue);
            Console.WriteLine(randomExpValue);
            */

        }
    }


}
