
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Controls;
using System.Globalization;
using System.Reflection;
using ArduinoAdmin.Lib;
using ArduinoAdmin.Formats;
using System.Net;
using System.Diagnostics;
using System.Text.RegularExpressions;
namespace ArduinoAdmin.Model
{
    /// <summary>
    /// Implémente la validation des propriétés
    /// </summary>
    public partial class Serveur
    {
        public Byte[] GetPhysicalAddress()
        {
            Byte[] adr = new Byte[6];
            int i = 0;
            foreach (var num in this.AdressePhysique.Split('-'))
            {
                if (i >= 6)
                    break;
                Byte.TryParse(num, out adr[i++]);
            }
            return adr;
        }

        public IPAddress GetIPAddress()
        {
            Byte[] adr = new Byte[4];
            int i = 0;
            foreach (var num in this.AdresseIP.Split('.'))
            {
                if (i >= 4)
                    break;
                Byte.TryParse(num, out adr[i++]);
            }
            return new IPAddress(adr);
        }

        public void SendMessage(Message message)
        {
            IPAddress Ip = GetIPAddress();
            Console.WriteLine("SendMessage:" + message.ToString());
            if (Ip != null)
            {
                EthernetSocket eth = new EthernetSocket(Ip);
                eth.SendMessage(message);
            }
        }

        public bool ResolveIP()
        {
            string output = String.Empty;
            Process p = null;
            // Execute la commande ARP
            try
            {
                p = Process.Start(new ProcessStartInfo("arp", "-a")
                {
                    CreateNoWindow = true,
                    UseShellExecute = false,
                    RedirectStandardOutput = true
                });

                output = p.StandardOutput.ReadToEnd();

                p.Close();
            }
            catch (Exception)
            {
                return false;
            }
            finally
            {
                if(p!=null)
                    p.Close();
            }

            // Lit la sortie a la recherche de l'adresse mac
            foreach(var str in output.Split(new char[] { '\n', '\r' }).ToList())
            {
                System.Text.RegularExpressions.Regex myRegex = new Regex(@"^\s*([0-9]+(?:\.[0-9]+){3})\s+([0-9a-fA-F]+(?:\-[0-9a-fA-F]+){5})");
                Match match = myRegex.Match(str);
                if (match.Success)
                {
                    if (match.Groups[2].Value.ToUpper() == AdressePhysique.ToUpper())
                    {
                        this.AdresseIP = match.Groups[1].Value;
                        Console.WriteLine("found io " + this.AdresseIP);
                        return true;
                    }
                }
            }

            Console.WriteLine("not found IP");
            return false;
        }
    }
}
