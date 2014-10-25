using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using ArduinoAdmin.Lib;

namespace ArduinoAdmin.Lib
{
    public interface IEventHandler
    {
        // traite un evenement
        void OnProcessEvent(object me, string name, object sender, object param);
    }
    public class ObservableCollectionEvent<T> : ObservableCollection<T>, IEventHandler
    {
        //-----------------------------------------------------------------------------------------
        // Evénements
        // Réceptionne les événements "utilisateur" provenant des autres fenêtres puis agit en conséquence.
        //-----------------------------------------------------------------------------------------
        #region Events
        public void OnProcessEvent(object me, string name, object sender, object param)
        {
            //passe aux contextes enfants
            foreach (var item in this.Items)
            {
                if (item is IEventHandler)
                    (item as IEventHandler).OnProcessEvent(me, name, sender, param);
            }
        }
        #endregion
    }
    public static class EventHandler
    {
        /// <summary>
        /// Liste les enfants de premier niveau
        /// </summary>
        /// <param name="obj">Objet parent</param>
        /// <param name="list">Liste recevant les objets enfants implémentant IEventHandler</param>
        /// <returns></returns>
        public static List<DependencyObject> EnumChildren(DependencyObject obj, List<DependencyObject> list)
        {
            int nChild = VisualTreeHelper.GetChildrenCount(obj);
            for (int i = 0; i < nChild; i++)
            {
                DependencyObject child = VisualTreeHelper.GetChild(obj, i);
                if (child as IEventHandler != null)
                {
                    list.Add(child);
                }
                else if (VisualTreeHelper.GetChildrenCount(child) > 0)
                {
                    EnumChildren(child, list);
                }
            }
            return list;
        }

        // implémentation générique pour un control
        public static void OnProcessControlEvent(Control ctrl, object me, string name, object sender, object param)
        {
#if (TRACE_VIEW_EVENTS)
            Console.WriteLine(String.Format("View event {0} (from {1} By {2})", name, sender, me));
#endif
            //passe l'evenement aux controles enfants
            List<DependencyObject> list = EventHandler.EnumChildren(ctrl, new List<DependencyObject>());
            foreach (DependencyObject obj in list)
            {
#if (TRACE_VIEW_EVENTS)
                Console.WriteLine(String.Format("  >>  OnProcessEvent to {0}", obj));
#endif
                (obj as IEventHandler).OnProcessEvent(me, name, sender, param);
            }
        }

        // implémentation générique pour un model
        public static void OnProcessModelEvent(IEventHandler model, object me, string name, object sender, object param)
        {
//            Console.WriteLine("OnProcessModelEvent... (from " + sender + ")");

            // passe l'evenement aux modeles enfants
            foreach (PropertyInfo p in model.GetType().GetProperties())
            {
                //
                IEventHandler child = p.GetValue(model) as IEventHandler;
                if (child != null)
                {
//                    Console.WriteLine("OnProcessModelEvent: " + p.Name);
                    child.OnProcessEvent(me, name, sender, param);
                    continue;
                }

                //si la propriete est une collection, enumere les enfants
                /*ICollection enumProp = p.GetValue(model) as ICollection;
                if (enumProp != null)
                {
                    //passe aux contextes enfants
                    foreach (IEventHandler item in enumProp)
                    {
                        item.OnProcessEvent(name, sender, param);
                        //EventHandler.OnProcessModelEvent(item as IEventHandler, name, sender, param);
                    }
                }*/
            }
        }
    }
}
