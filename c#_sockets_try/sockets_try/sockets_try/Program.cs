using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Collections;

namespace sockets_try
{
    class Server
    {
        Socket conn;
        public Server(Socket sock)
        {
            conn = sock;
        }
        public void WorkWithClients()
        {

            byte[] bytes = new byte[1024];
            int bytesRec = conn.Receive(bytes);
            string data = Encoding.UTF8.GetString(bytes, 0, bytesRec);
            Console.WriteLine(data);
            string addr = ((IPEndPoint) conn.RemoteEndPoint).Address.ToString();
            Console.WriteLine(addr + " has disconnected.");
            conn.Close();

           // Console.WriteLine(conn.RemoteEndPoint.AddressFamily + " has disconnected.");
        }
    }
    class Program
    {

        static void Main(string[] args)
        {
            Console.WriteLine("Server");
            IPHostEntry ipHost = Dns.GetHostEntry("localhost");
          // IPAddress ipAddr = IPAddress.Parse("10.64.18.17");
           IPAddress ipAddr = ipHost.AddressList[0];//4th number was defined by experience
            string addr = Dns.GetHostEntry("127.0.0.1").AddressList[0].ToString();
            Console.WriteLine(addr);
          //  Console.WriteLine(Dns.GetHostEntry("127.0.0.1").AddressList[0].ToString());
            IPEndPoint ipEP = new IPEndPoint(ipAddr, 61390);
            Socket servSock = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            servSock.Bind(ipEP);
            servSock.Listen(10);
            List<Thread> connections = new List<Thread>();
            while (true)
            {
                Socket conn = servSock.Accept();
                Console.WriteLine(conn.AddressFamily.ToString() + "  connected.");
                Server srv = new Server(conn);
                ThreadStart threadDelegate = new ThreadStart(srv.WorkWithClients);
                Thread clThread = new Thread(threadDelegate);
                clThread.Start();
                clThread.Join();
                connections.Add(clThread);
            }

        }
    }
}
