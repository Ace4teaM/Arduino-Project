/*
   Vue d'édition de la classe CommandeArgument

   !!Attention!!
   Ce code source est généré automatiquement, toutes modifications sera perdue
   
*/

using System;
using System.Windows;
using System.Windows.Controls;
namespace ArduinoAdmin.View
{
    /// <summary>
    /// Logique d'interaction pour Edit_CommandeArgument.xaml
    /// </summary>
    public partial class Edit_CommandeArgument : UserControl
    {
        public Edit_CommandeArgument()
        {
            InitializeComponent();
            Mode = EditWnd.EditMode.Other;
        }

        public Edit_CommandeArgument(EditWnd.EditMode mode)
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
        public static readonly DependencyProperty EnabledItemsProperty = DependencyProperty.Register("EnabledItems", typeof(string), typeof(Edit_CommandeArgument), new PropertyMetadata(string.Empty, EnabledItemsChanged));
        public string EnabledItems
        {
            get { return (string)base.GetValue(EnabledItemsProperty); }
            set { base.SetValue(EnabledItemsProperty, value); }
        }

        private static void EnabledItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_CommandeArgument;

             string[] _args = me.EnabledItems.Split(new char[]{','},StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_COMMANDE_ARGUMENT_ID.IsEnabled = false;
             me.itemGroup_DESCRIPTION.IsEnabled = false;
             me.itemGroup_TYPEVALEUR.IsEnabled = false;
             me.itemGroup_NOM.IsEnabled = false;             

             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "COMMANDE_ARGUMENT_ID":
                         me.itemGroup_COMMANDE_ARGUMENT_ID.IsEnabled = true;
                         break;
                     case "DESCRIPTION":
                         me.itemGroup_DESCRIPTION.IsEnabled = true;
                         break;
                     case "TYPEVALEUR":
                         me.itemGroup_TYPEVALEUR.IsEnabled = true;
                         break;
                     case "NOM":
                         me.itemGroup_NOM.IsEnabled = true;
                         break;
               }
            }
        }
        #endregion
        #region VisibleItems
        /// <summary>
        /// Définit les éléments visibles du dialogue
        /// </summary>
        public static readonly DependencyProperty VisibleItemsProperty = DependencyProperty.Register("VisibleItems", typeof(string), typeof(Edit_CommandeArgument), new PropertyMetadata(string.Empty, VisibleItemsChanged));
        public string VisibleItems
        {
            get { return (string)base.GetValue(VisibleItemsProperty); }
            set { base.SetValue(VisibleItemsProperty, value); }
        }

        private static void VisibleItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_CommandeArgument;

             string[] _args = me.VisibleItems.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_COMMANDE_ARGUMENT_ID.Visibility = Visibility.Collapsed;
             me.itemGroup_DESCRIPTION.Visibility = Visibility.Collapsed;
             me.itemGroup_TYPEVALEUR.Visibility = Visibility.Collapsed;
             me.itemGroup_NOM.Visibility = Visibility.Collapsed;             


             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "COMMANDE_ARGUMENT_ID":
                         me.itemGroup_COMMANDE_ARGUMENT_ID.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_COMMANDE_ARGUMENT_ID);
                         me.itemGroups.Children.Add(me.itemGroup_COMMANDE_ARGUMENT_ID);
                         break;
                     case "DESCRIPTION":
                         me.itemGroup_DESCRIPTION.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_DESCRIPTION);
                         me.itemGroups.Children.Add(me.itemGroup_DESCRIPTION);
                         break;
                     case "TYPEVALEUR":
                         me.itemGroup_TYPEVALEUR.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_TYPEVALEUR);
                         me.itemGroups.Children.Add(me.itemGroup_TYPEVALEUR);
                         break;
                     case "NOM":
                         me.itemGroup_NOM.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_NOM);
                         me.itemGroups.Children.Add(me.itemGroup_NOM);
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
                this.itemGroup_COMMANDE_ARGUMENT_ID.Visibility = Visibility.Visible;
                this.itemGroup_DESCRIPTION.Visibility = Visibility.Visible;
                this.itemGroup_TYPEVALEUR.Visibility = Visibility.Visible;
                this.itemGroup_NOM.Visibility = Visibility.Visible;                

                // active / desactive l'édition
                switch (value as EditWnd.EditMode?)
                {
                    case EditWnd.EditMode.ReadOnly:
                        this.itemGroup_COMMANDE_ARGUMENT_ID.IsEnabled = false;
                        this.itemGroup_DESCRIPTION.IsEnabled = false;
                        this.itemGroup_TYPEVALEUR.IsEnabled = false;
                        this.itemGroup_NOM.IsEnabled = false;
                      break;
                    default:
                        this.itemGroup_COMMANDE_ARGUMENT_ID.IsEnabled = false; //<< par defaut les identifiants ne sont pas editable
                        this.itemGroup_DESCRIPTION.IsEnabled = true;
                        this.itemGroup_TYPEVALEUR.IsEnabled = true;
                        this.itemGroup_NOM.IsEnabled = true;
                      break;
                }
            }
        }
        #endregion
        #endregion
    }
}