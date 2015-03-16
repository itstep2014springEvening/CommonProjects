using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication15
{

    class Man
    {
        public event EventHandler WorkEnded;
        public string name;
        public Man(string name) {
            this.name = name;
        }
        public void Work()
        {
            // поработали....

            // закончили
            if (WorkEnded != null)
            {
                WorkEnded(this, EventArgs.Empty);
            }
        }


    }

    class Program
    {
        static void ManWorkEndedHanler(object sender, EventArgs e)
        {
            Console.WriteLine("Теперь можно домой!");
        }

        public delegate bool check(int value);

        static public bool isOdd(int value)
        {
            return (value % 2) == 1;
        }

        static List<int> filter(List<int> list, check ch) {
            List<int> result = new List<int>();
            foreach(int x in list) {
                if (ch(x)) {
                    result.Add(x);
                }
            }
            return result;
        }

        static void Main(string[] args)
        {
            //vector<int> x {1,2,5,6};
            //removeif (x.begin(),x.end(), 
            //   [] (int a) {return a%2; })
            //
            List<int> l = new List<int> { 1, 2, 4, 6, 4, 7, 2, 5 };
            check ch = new check(isOdd);
            //l = filter(l, ch);
            l = filter(l, delegate (int value)
                {
                    return (value % 2) == 1;
                }
            );
            foreach (int x in l)
            {
                Console.WriteLine(x);
            }

            Man Eleonor = new Man("Eleonor Rigby");

            Eleonor.WorkEnded += new EventHandler(ManWorkEndedHanler);

         



            Eleonor.Work();
        }
    }
}
