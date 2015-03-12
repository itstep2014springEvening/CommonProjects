using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication14
{
    class Event
    {
        public readonly uint time;
        public Event(uint time)
        {
            this.time = time;
        }
        public virtual void process() { }
    }

    class NewPassangerEvent : Event
    {
        public readonly Stop where;
        public NewPassangerEvent(uint time, Stop where) : base(time) {
            this.where = where;
        }

        public override void process()
        {
            new Passanger(where);
        }


    }

    class Stop
    {
        public List<Passanger> passangers;
        public readonly uint timeToNext;
        public readonly uint passangerInterval;
        public readonly string name;
        public Stop(string name, uint timeToNext, uint passangerInterval)
        {
            this.name = name;
            this.timeToNext = timeToNext;
            this.passangerInterval = passangerInterval;
            this.passangers = new List<Passanger>();
        }
    }
    class Passanger
    {
        readonly uint arrival;
        readonly Stop stop;
        public Passanger(Stop stop)
        {
            this.stop.passangers.Add(this);

            arrival = Program.time;
            uint nextArrival = Program.time + 3;
            Program.events.Add(new NewPassangerEvent( nextArrival, stop));

        }
    }

    class Program
    {
        public static uint time;
        public static List<Event> events;
        public static List<Stop> stops;
        static void Main(string[] args)
        {
            time = 0;
            stops = new List<Stop>(){
                new Stop("Kastrychnickaja", 200, 3),
                new Stop("Niamiha", 180, 6),
                new Stop("Frunzenskaja", 190, 5),
                new Stop("Niamiha", 300, 6)
            };

            events = new List<Event>() {
                new NewPassangerEvent(1,stops[0]),
                new NewPassangerEvent(2,stops[1]),
                new NewPassangerEvent(3,stops[2]),
                new NewPassangerEvent(5,stops[3])
            };

            while (time < 10) {
                uint mintime = events[0].time;
                Event upcomingEvent = events[0];
                foreach (Event ev in events)
                {
                    if (ev.time < mintime)
                    {
                        mintime = ev.time;
                        upcomingEvent = ev;
                    }
                }
                upcomingEvent.process();

            }

        }
    }
}
