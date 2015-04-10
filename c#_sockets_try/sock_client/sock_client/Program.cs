using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;


namespace sock_client
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Client");
            Console.WriteLine("Enter IP address:");
            string addr = Console.ReadLine();
            IPAddress ipAddr = IPAddress.Parse(addr);
            IPEndPoint ipEP = new IPEndPoint(ipAddr, 61390);
            Socket client = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            client.Connect(ipEP);
            client.Send(Encoding.ASCII.GetBytes("Hello, World!"));
            bool isConnected = true;
            client.Disconnect(isConnected);
            client.Close();
        }
    }
}
