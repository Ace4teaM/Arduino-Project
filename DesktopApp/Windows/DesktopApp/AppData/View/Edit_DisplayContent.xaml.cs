/*
   Vue d'édition de la classe DisplayContent

   !!Attention!!
   Ce code source est généré automatiquement, toutes modifications sera perdue
   
*/

using System;
using System.Windows;
using System.Windows.Controls;
namespace AppData.View
{
    /// <summary>
    /// Logique d'interaction pour Edit_DisplayContent.xaml
    /// </summary>
    public partial class Edit_DisplayContent : UserControl
    {
        public Edit_DisplayContent()
        {
            InitializeComponent();
        }

        //-----------------------------------------------------------------------------------------
        // Proprietes
        //-----------------------------------------------------------------------------------------
        #region Properties
        #region EnabledItems
        /// <summary>
        /// Définit les éléments actifs du dialogue
        /// </summary>
        public static readonly DependencyProperty EnabledItemsProperty = DependencyProperty.Register("EnabledItems", typeof(string), typeof(Edit_DisplayContent), new PropertyMetadata(string.Empty, EnabledItemsChanged));
        public string EnabledItems
        {
            get { return (string)base.GetValue(EnabledItemsProperty); }
            set { base.SetValue(EnabledItemsProperty, value); }
        }

        private static void EnabledItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_DisplayContent;

             string[] _args = me.EnabledItems.Split(new char[]{','},StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_w.IsEnabled = false;
             me.itemGroup_h.IsEnabled = false;
             me.itemGroup_x.IsEnabled = false;
             me.itemGroup_y.IsEnabled = false;             

             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "w":
                         me.itemGroup_w.IsEnabled = true;
                         break;
                     case "h":
                         me.itemGroup_h.IsEnabled = true;
                         break;
                     case "x":
                         me.itemGroup_x.IsEnabled = true;
                         break;
                     case "y":
                         me.itemGroup_y.IsEnabled = true;
                         break;
               }
            }
        }
        #endregion
        #region VisibleItems
        /// <summary>
        /// Définit les éléments visibles du dialogue
        /// </summary>
        public static readonly DependencyProperty VisibleItemsProperty = DependencyProperty.Register("VisibleItems", typeof(string), typeof(Edit_DisplayContent), new PropertyMetadata(string.Empty, VisibleItemsChanged));
        public string VisibleItems
        {
            get { return (string)base.GetValue(VisibleItemsProperty); }
            set { base.SetValue(VisibleItemsProperty, value); }
        }

        private static void VisibleItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_DisplayContent;

             string[] _args = me.VisibleItems.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_w.Visibility = Visibility.Collapsed;
             me.itemGroup_h.Visibility = Visibility.Collapsed;
             me.itemGroup_x.Visibility = Visibility.Collapsed;
             me.itemGroup_y.Visibility = Visibility.Collapsed;             


             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "w":
                         me.itemGroup_w.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_w);
                         me.itemGroups.Children.Add(me.itemGroup_w);
                         break;
                     case "h":
                         me.itemGroup_h.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_h);
                         me.itemGroups.Children.Add(me.itemGroup_h);
                         break;
                     case "x":
                         me.itemGroup_x.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_x);
                         me.itemGroups.Children.Add(me.itemGroup_x);
                         break;
                     case "y":
                         me.itemGroup_y.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_y);
                         me.itemGroups.Children.Add(me.itemGroup_y);
                         break;
              }
            }
        }
        #endregion
        #region Editable
        /// <summary>
        /// Indique si les champs sont éditables
        /// </summary>
        private bool editable;
        public bool Editable
        {
            get { return editable; }
            set {
               this.editable = value;
               
                // rend les éléments visibles
                this.itemGroup_w.Visibility = Visibility.Visible;
                this.itemGroup_h.Visibility = Visibility.Visible;
                this.itemGroup_x.Visibility = Visibility.Visible;
                this.itemGroup_y.Visibility = Visibility.Visible;                

                // active / desactive l'édition
               this.itemGroup_w.IsEnabled = value;
               this.itemGroup_h.IsEnabled = value;
               this.itemGroup_x.IsEnabled = value;
               this.itemGroup_y.IsEnabled = value;

            }
        }
        #endregion
        #endregion
    }
}