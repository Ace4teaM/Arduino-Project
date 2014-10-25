/*
   Vue d'édition de la classe Commande

   !!Attention!!
   Ce code source est généré automatiquement, toutes modifications sera perdue
   
*/

using System;
using System.Windows;
using System.Windows.Controls;
using ArduinoAdmin.Fenetres;
namespace ArduinoAdmin.Vues
{
    /// <summary>
    /// Logique d'interaction pour Edit_Commande.xaml
    /// </summary>
    public partial class Edit_Commande : UserControl
    {
        public Edit_Commande()
        {
            InitializeComponent();
            Mode = EditWnd.EditMode.Other;
        }

        public Edit_Commande(EditWnd.EditMode mode)
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
        public static readonly DependencyProperty EnabledItemsProperty = DependencyProperty.Register("EnabledItems", typeof(string), typeof(Edit_Commande), new PropertyMetadata(string.Empty, EnabledItemsChanged));
        public string EnabledItems
        {
            get { return (string)base.GetValue(EnabledItemsProperty); }
            set { base.SetValue(EnabledItemsProperty, value); }
        }

        private static void EnabledItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_Commande;

             string[] _args = me.EnabledItems.Split(new char[]{','},StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_Commande_Id.IsEnabled = false;
             me.itemGroup_Description.IsEnabled = false;
             me.itemGroup_CodeCmd.IsEnabled = false;
             me.itemGroup_CmdParams.IsEnabled = false;             

             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "Commande_Id":
                         me.itemGroup_Commande_Id.IsEnabled = true;
                         break;
                     case "Description":
                         me.itemGroup_Description.IsEnabled = true;
                         break;
                     case "CodeCmd":
                         me.itemGroup_CodeCmd.IsEnabled = true;
                         break;
                     case "CmdParams":
                         me.itemGroup_CmdParams.IsEnabled = true;
                         break;
               }
            }
        }
        #endregion
        #region VisibleItems
        /// <summary>
        /// Définit les éléments visibles du dialogue
        /// </summary>
        public static readonly DependencyProperty VisibleItemsProperty = DependencyProperty.Register("VisibleItems", typeof(string), typeof(Edit_Commande), new PropertyMetadata(string.Empty, VisibleItemsChanged));
        public string VisibleItems
        {
            get { return (string)base.GetValue(VisibleItemsProperty); }
            set { base.SetValue(VisibleItemsProperty, value); }
        }

        private static void VisibleItemsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var me = d as Edit_Commande;

             string[] _args = me.VisibleItems.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

             // desactive tout
             me.itemGroup_Commande_Id.Visibility = Visibility.Collapsed;
             me.itemGroup_Description.Visibility = Visibility.Collapsed;
             me.itemGroup_CodeCmd.Visibility = Visibility.Collapsed;
             me.itemGroup_CmdParams.Visibility = Visibility.Collapsed;             


             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "Commande_Id":
                         me.itemGroup_Commande_Id.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Commande_Id);
                         me.itemGroups.Children.Add(me.itemGroup_Commande_Id);
                         break;
                     case "Description":
                         me.itemGroup_Description.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Description);
                         me.itemGroups.Children.Add(me.itemGroup_Description);
                         break;
                     case "CodeCmd":
                         me.itemGroup_CodeCmd.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_CodeCmd);
                         me.itemGroups.Children.Add(me.itemGroup_CodeCmd);
                         break;
                     case "CmdParams":
                         me.itemGroup_CmdParams.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_CmdParams);
                         me.itemGroups.Children.Add(me.itemGroup_CmdParams);
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
                this.itemGroup_Commande_Id.Visibility = Visibility.Visible;
                this.itemGroup_Description.Visibility = Visibility.Visible;
                this.itemGroup_CodeCmd.Visibility = Visibility.Visible;
                this.itemGroup_CmdParams.Visibility = Visibility.Visible;                

                // active / desactive l'édition
                switch (value as EditWnd.EditMode?)
                {
                    case EditWnd.EditMode.ReadOnly:
                        this.itemGroup_Commande_Id.IsEnabled = false;
                        this.itemGroup_Description.IsEnabled = false;
                        this.itemGroup_CodeCmd.IsEnabled = false;
                        this.itemGroup_CmdParams.IsEnabled = false;
                      break;
                    default:
                        this.itemGroup_Commande_Id.IsEnabled = false; //<< par defaut les identifiants ne sont pas editable
                        this.itemGroup_Description.IsEnabled = true;
                        this.itemGroup_CodeCmd.IsEnabled = true;
                        this.itemGroup_CmdParams.IsEnabled = true;
                      break;
                }
            }
        }
        #endregion
        #endregion
    }
}