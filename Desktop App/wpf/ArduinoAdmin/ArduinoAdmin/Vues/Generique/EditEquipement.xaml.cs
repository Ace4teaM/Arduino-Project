/*
   Vue d'édition de la classe Equipement

   !!Attention!!
   Ce code source est généré automatiquement, toutes modifications sera perdue
   
*/

using System;
using System.Windows;
using System.Windows.Controls;
namespace ArduinoAdmin.View
{
    /// <summary>
    /// Logique d'interaction pour Edit_Equipement.xaml
    /// </summary>
    public partial class Edit_Equipement : UserControl
    {
        public Edit_Equipement()
        {
            InitializeComponent();
            Mode = EditWnd.EditMode.Other;
        }

        public Edit_Equipement(EditWnd.EditMode mode)
            : this()
        {
            Mode = mode;
        }

        //-----------------------------------------------------------------------------------------
        // Proprietes
        //-----------------------------------------------------------------------------------------
        #region Properties
        #region EnabledItems
        /// <summary>
        /// Définit les éléments actifs du dialogue
        /// </summary>
        public static readonly DependencyProperty EnabledItemsProperty = DependencyProperty.Register("EnabledItems", typeof(string), typeof(Edit_Equipement), new PropertyMetadata(string.Empty, EnabledItemsChanged));
        public string EnabledItems
        {
            get { return (string)base.GetValue(EnabledItemsProperty); }
            set { base.SetValue(EnabledItemsProperty, value); }
        }

        private static void EnabledItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_Equipement;

             string[] _args = me.EnabledItems.Split(new char[]{','},StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_EQUIPEMENT_ID.IsEnabled = false;
             me.itemGroup_DESCRIPTION.IsEnabled = false;
             me.itemGroup_RXPINNUM.IsEnabled = false;
             me.itemGroup_TXPINNUM.IsEnabled = false;             

             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "EQUIPEMENT_ID":
                         me.itemGroup_EQUIPEMENT_ID.IsEnabled = true;
                         break;
                     case "DESCRIPTION":
                         me.itemGroup_DESCRIPTION.IsEnabled = true;
                         break;
                     case "RXPINNUM":
                         me.itemGroup_RXPINNUM.IsEnabled = true;
                         break;
                     case "TXPINNUM":
                         me.itemGroup_TXPINNUM.IsEnabled = true;
                         break;
               }
            }
        }
        #endregion
        #region VisibleItems
        /// <summary>
        /// Définit les éléments visibles du dialogue
        /// </summary>
        public static readonly DependencyProperty VisibleItemsProperty = DependencyProperty.Register("VisibleItems", typeof(string), typeof(Edit_Equipement), new PropertyMetadata(string.Empty, VisibleItemsChanged));
        public string VisibleItems
        {
            get { return (string)base.GetValue(VisibleItemsProperty); }
            set { base.SetValue(VisibleItemsProperty, value); }
        }

        private static void VisibleItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_Equipement;

             string[] _args = me.VisibleItems.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_EQUIPEMENT_ID.Visibility = Visibility.Collapsed;
             me.itemGroup_DESCRIPTION.Visibility = Visibility.Collapsed;
             me.itemGroup_RXPINNUM.Visibility = Visibility.Collapsed;
             me.itemGroup_TXPINNUM.Visibility = Visibility.Collapsed;             


             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "EQUIPEMENT_ID":
                         me.itemGroup_EQUIPEMENT_ID.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_EQUIPEMENT_ID);
                         me.itemGroups.Children.Add(me.itemGroup_EQUIPEMENT_ID);
                         break;
                     case "DESCRIPTION":
                         me.itemGroup_DESCRIPTION.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_DESCRIPTION);
                         me.itemGroups.Children.Add(me.itemGroup_DESCRIPTION);
                         break;
                     case "RXPINNUM":
                         me.itemGroup_RXPINNUM.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_RXPINNUM);
                         me.itemGroups.Children.Add(me.itemGroup_RXPINNUM);
                         break;
                     case "TXPINNUM":
                         me.itemGroup_TXPINNUM.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_TXPINNUM);
                         me.itemGroups.Children.Add(me.itemGroup_TXPINNUM);
                         break;
              }
            }
        }
        #endregion
        #region EditMode
        /// <summary>
        /// Indique le mode d'édition de la fenêtre
        /// </summary>
        /// <remarks>
        /// Le mode permet de verrouiller ou non les champs en lecture seules
        /// </remarks>
        private EditWnd.EditMode editMode;
        public EditWnd.EditMode Mode
        {
            get { return editMode; }
            set {
               this.editMode = value;
               
                // rend les éléments visibles
                this.itemGroup_EQUIPEMENT_ID.Visibility = Visibility.Visible;
                this.itemGroup_DESCRIPTION.Visibility = Visibility.Visible;
                this.itemGroup_RXPINNUM.Visibility = Visibility.Visible;
                this.itemGroup_TXPINNUM.Visibility = Visibility.Visible;                

                // active / desactive l'édition
                switch (value as EditWnd.EditMode?)
                {
                    case EditWnd.EditMode.ReadOnly:
                        this.itemGroup_EQUIPEMENT_ID.IsEnabled = false;
                        this.itemGroup_DESCRIPTION.IsEnabled = false;
                        this.itemGroup_RXPINNUM.IsEnabled = false;
                        this.itemGroup_TXPINNUM.IsEnabled = false;
                      break;
                    default:
                        this.itemGroup_EQUIPEMENT_ID.IsEnabled = false; //<< par defaut les identifiants ne sont pas editable
                        this.itemGroup_DESCRIPTION.IsEnabled = true;
                        this.itemGroup_RXPINNUM.IsEnabled = true;
                        this.itemGroup_TXPINNUM.IsEnabled = true;
                      break;
                }
            }
        }
        #endregion
        #endregion
    }
}