using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using AppData.Entity;
using Lib;
using System.IO;
using System.Xml;
using AppData.View;
using DesktopApp.Event;

namespace DesktopApp.ModelView
{
    class MainWindow : ViewModelBase
    {
        App app = Application.Current as App;
        public MainWindow()
        {
        }

        //-----------------------------------------------------------------------------------------
        // Commandes
        //-----------------------------------------------------------------------------------------
        #region Commands
        #region CreateArduinoServer
        private ICommand createArduinoServer;
        public ICommand CreateArduinoServer
        {
            get
            {
                if (this.createArduinoServer == null)
                    this.createArduinoServer = new DelegateCommand(() =>
                    {
                        ArduinoServer entity = new ArduinoServer(Guid.NewGuid().ToString(), "127.0.0.1");
                        Edit_ArduinoServer view = new Edit_ArduinoServer();
                        view.Width = 300;
                        view.DataContext = entity;
                        EditWindow wnd = new EditWindow("Arduino Serveur",view);
                        wnd.Owner = app.MainWindow;
                        wnd.View.AddButton("Insérer", delegate(object s, RoutedEventArgs re)
                        {
                            wnd.DialogResult = true;
                            wnd.Close();
                        });
                        if (wnd.ShowDialog() == true)
                        {
                            app.Project.AddArduinoServer(entity);
                            app.ProcessEvent(this, this, new EntityCreateEvent(entity));
                        }
                    });

                return this.createArduinoServer;
            }
        }
        #endregion
        #region CreateDisplayContent
        private ICommand createDisplayContent;
        public ICommand CreateDisplayContent
        {
            get
            {
                if (this.createDisplayContent == null)
                    this.createDisplayContent = new DelegateCommand(() =>
                    {
                        DisplayContent entity = new DisplayContent(100,100,10,10);
                        Edit_DisplayContent view = new Edit_DisplayContent();
                        view.Width = 300;
                        view.DataContext = entity;
                        EditWindow wnd = new EditWindow("Vue", view);
                        wnd.Owner = app.MainWindow;
                        wnd.View.AddButton("Insérer", delegate(object s, RoutedEventArgs re)
                        {
                            wnd.DialogResult = true;
                            wnd.Close();
                        });
                        if (wnd.ShowDialog() == true)
                        {
                            app.Project.AddDisplayContent(entity);
                            app.ProcessEvent(this, this, new EntityCreateEvent(entity));
                        }
                    });

                return this.createDisplayContent;
            }
        }
        #endregion
        #region OpenFile
        private ICommand openFile;
        public ICommand OpenFile
        {
            get
            {
                if (this.openFile == null)
                    this.openFile = new DelegateCommand(() =>
                    {
                    });

                return this.openFile;
            }
        }
        #endregion
        #region Exit
        private ICommand exit;
        public ICommand Exit
        {
            get
            {
                if (this.exit == null)
                    this.exit = new DelegateCommand(() =>
                    {
                        Application.Current.Shutdown();
                    });

                return this.exit;
            }
        }
        #endregion
        #endregion
    }
}
