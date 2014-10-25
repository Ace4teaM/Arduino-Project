/*
   Vue d'édition de la classe Equipement

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
             me.itemGroup_Equipement_Id.IsEnabled = false;
             me.itemGroup_Nom.IsEnabled = false;
             me.itemGroup_Description.IsEnabled = false;
             me.itemGroup_RxPinNum.IsEnabled = false;
             me.itemGroup_TxPinNum.IsEnabled = false;
             me.itemGroup_Px.IsEnabled = false;
             me.itemGroup_Py.IsEnabled = false;
             me.itemGroup_Pz.IsEnabled = false;             

             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "Equipement_Id":
                         me.itemGroup_Equipement_Id.IsEnabled = true;
                         break;
                     case "Nom":
                         me.itemGroup_Nom.IsEnabled = true;
                         break;
                     case "Description":
                         me.itemGroup_Description.IsEnabled = true;
                         break;
                     case "RxPinNum":
                         me.itemGroup_RxPinNum.IsEnabled = true;
                         break;
                     case "TxPinNum":
                         me.itemGroup_TxPinNum.IsEnabled = true;
                         break;
                     case "Px":
                         me.itemGroup_Px.IsEnabled = true;
                         break;
                     case "Py":
                         me.itemGroup_Py.IsEnabled = true;
                         break;
                     case "Pz":
                         me.itemGroup_Pz.IsEnabled = true;
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
             me.itemGroup_Equipement_Id.Visibility = Visibility.Collapsed;
             me.itemGroup_Nom.Visibility = Visibility.Collapsed;
             me.itemGroup_Description.Visibility = Visibility.Collapsed;
             me.itemGroup_RxPinNum.Visibility = Visibility.Collapsed;
             me.itemGroup_TxPinNum.Visibility = Visibility.Collapsed;
             me.itemGroup_Px.Visibility = Visibility.Collapsed;
             me.itemGroup_Py.Visibility = Visibility.Collapsed;
             me.itemGroup_Pz.Visibility = Visibility.Collapsed;             


             // active les éléments demandés
             foreach (string s in _args)
             {
                 switch (s.Trim())
                 {
                     case "Equipement_Id":
                         me.itemGroup_Equipement_Id.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Equipement_Id);
                         me.itemGroups.Children.Add(me.itemGroup_Equipement_Id);
                         break;
                     case "Nom":
                         me.itemGroup_Nom.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Nom);
                         me.itemGroups.Children.Add(me.itemGroup_Nom);
                         break;
                     case "Description":
                         me.itemGroup_Description.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Description);
                         me.itemGroups.Children.Add(me.itemGroup_Description);
                         break;
                     case "RxPinNum":
                         me.itemGroup_RxPinNum.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_RxPinNum);
                         me.itemGroups.Children.Add(me.itemGroup_RxPinNum);
                         break;
                     case "TxPinNum":
                         me.itemGroup_TxPinNum.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_TxPinNum);
                         me.itemGroups.Children.Add(me.itemGroup_TxPinNum);
                         break;
                     case "Px":
                         me.itemGroup_Px.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Px);
                         me.itemGroups.Children.Add(me.itemGroup_Px);
                         break;
                     case "Py":
                         me.itemGroup_Py.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Py);
                         me.itemGroups.Children.Add(me.itemGroup_Py);
                         break;
                     case "Pz":
                         me.itemGroup_Pz.Visibility = Visibility.Visible;
                         // place l'élément en bas de la pile (permet le tri par visibilité)
                         me.itemGroups.Children.Remove(me.itemGroup_Pz);
                         me.itemGroups.Children.Add(me.itemGroup_Pz);
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
                this.itemGroup_Equipement_Id.Visibility = Visibility.Visible;
                this.itemGroup_Nom.Visibility = Visibility.Visible;
                this.itemGroup_Description.Visibility = Visibility.Visible;
                this.itemGroup_RxPinNum.Visibility = Visibility.Visible;
                this.itemGroup_TxPinNum.Visibility = Visibility.Visible;
                this.itemGroup_Px.Visibility = Visibility.Visible;
                this.itemGroup_Py.Visibility = Visibility.Visible;
                this.itemGroup_Pz.Visibility = Visibility.Visible;                

                // active / desactive l'édition
                switch (value as EditWnd.EditMode?)
                {
                    case EditWnd.EditMode.ReadOnly:
                        this.itemGroup_Equipement_Id.IsEnabled = false;
                        this.itemGroup_Nom.IsEnabled = false;
                        this.itemGroup_Description.IsEnabled = false;
                        this.itemGroup_RxPinNum.IsEnabled = false;
                        this.itemGroup_TxPinNum.IsEnabled = false;
                        this.itemGroup_Px.IsEnabled = false;
                        this.itemGroup_Py.IsEnabled = false;
                        this.itemGroup_Pz.IsEnabled = false;
                      break;
                    default:
                        this.itemGroup_Equipement_Id.IsEnabled = false; //<< par defaut les identifiants ne sont pas editable
                        this.itemGroup_Nom.IsEnabled = true;
                        this.itemGroup_Description.IsEnabled = true;
                        this.itemGroup_RxPinNum.IsEnabled = true;
                        this.itemGroup_TxPinNum.IsEnabled = true;
                        this.itemGroup_Px.IsEnabled = true;
                        this.itemGroup_Py.IsEnabled = true;
                        this.itemGroup_Pz.IsEnabled = true;
                      break;
                }
            }
        }
        #endregion
        #endregion
    }
}