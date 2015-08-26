using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Windows;
using AppData.Entity;
using Lib;

namespace DesktopApp
{
    /// <summary>
    /// Logique d'interaction pour App.xaml
    /// </summary>
    public partial class App : Application, IEventProcess
    {
        public Project Project{get;set;}

        public App()
        {
            Project = new Project("Sans Titre");
        }

        //-----------------------------------------------------------------------------------------
        // IEventProcess
        //-----------------------------------------------------------------------------------------
        public void ProcessEvent(object from, object _this, IEvent e)
        {
            if (this.MainWindow != null && this.MainWindow is IEventProcess)
                (this.MainWindow as IEventProcess).ProcessEvent(from, this, e);
        }
    }
}
