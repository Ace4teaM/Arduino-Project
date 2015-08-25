using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Windows;
using AppData.Entity;

namespace DesktopApp
{
    /// <summary>
    /// Logique d'interaction pour App.xaml
    /// </summary>
    public partial class App : Application
    {
        public Project Project{get;set;}

        public App()
        {
            Project = new Project("Sans Titre");
        }
    }
}
