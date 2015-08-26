using System;
using System.Collections.Generic;
using System.Linq;
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
using AppData.Entity;
using DesktopApp.Event;
using Lib;

namespace DesktopApp.View
{
    /// <summary>
    /// Logique d'interaction pour ProjectTreeView.xaml
    /// </summary>
    public partial class ProjectTreeView : TreeView, IEventProcess
    {
        public ProjectTreeView()
        {
            InitializeComponent();
        }

        //-----------------------------------------------------------------------------------------
        // IEventProcess
        //-----------------------------------------------------------------------------------------
        public void ProcessEvent(object from, object _this, IEvent e)
        {
            if (e is EntityCreateEvent)
            {
                EntityCreateEvent dat = e as EntityCreateEvent;

                if (dat.Entity is ArduinoServer)
                {
                    TreeViewItem item = new TreeViewItem();
                    item.Tag = dat.Entity;
                    item.Header = (dat.Entity as ArduinoServer).Ipv4;
                    this.serversItem.Items.Add(item);
                }

                if (dat.Entity is DisplayContent)
                {
                    TreeViewItem item = new TreeViewItem();
                    item.Tag = dat.Entity;
                    item.Header = "DisplayContent";
                    this.viewsItem.Items.Add(item);
                }
            }
        }
    }
}
