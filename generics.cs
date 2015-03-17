using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace generics
{
    struct PlainVector<T> where T: IComparable
    {
        public T x, y;
        public PlainVector(T x, T y)
        {
            this.x = x;
            this.y = y;
        }
        /*public static PlainVector<T> plus(PlainVector<T> a, PlainVector<T> b)
        {
            return new PlainVector<T>(a.x + b.x, a.y + b.y);
        }*/
        public static explicit operator string(PlainVector<T> a)
        {
            return String.Format("({0};{1})",a.x,a.y);
        }
        
    }
    class Program
    {
        static void Main(string[] args)
        {
            PlainVector<double>
                a = new PlainVector<double>(1, 2),
                b = new PlainVector<double>(2, 3),
                c;
            //c = a+b;
            //string s = (string)c;
            //Console.WriteLine(s);

            SortedDictionary<string, PlainVector<int>> z = new SortedDictionary<string, PlainVector<int>>();
            z["Ololino"] = new PlainVector<int>(12, 23);
            z["Atolino"] = new PlainVector<int>(22, 13);
            z["Bulbolino"] = new PlainVector<int>(14, 43);

            foreach (KeyValuePair<string, PlainVector<int>> p in z)
            {
                Console.WriteLine("{0} is at {1}", p.Key, (string)p.Value);
            }
           
        }
    }
}
