using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ArduinoAdmin.Lib;

namespace ArduinoAdmin
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Message message=new Message(Message.MessageType.Command);
            message.Parameters.Add("equipId", "0");
            message.Parameters.Add("codeCmd", "Hello");
            Console.WriteLine(message.ToString());
            EthernetSocket eth = new EthernetSocket(new IPAddress(new byte[]{192,168,1,30}));
            eth.SendMessage(message);
        }
    }
}
