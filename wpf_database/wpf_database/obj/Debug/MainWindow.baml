   M S B A M L   `   `   `  ����G  Cwpf_database, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null+clr-namespace:wpf_databasewpf_database  5   	       wpf_database.MainWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35U QWPFToolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   ,localclr-namespace:wpf_database     5   	   :Custom-http://schemas.microsoft.com/wpf/2008/toolkit  5   	   -   5          � Title$  
MainWindow��5	   	    � SizeToContent$ WidthAndHeight=�6   $	��350��6;   $	��700��6H   .��5
      �� $
��Left=�6   $	��321��6,   $	��Top=�69   $	��515��6Q   $��0,0,0,-2q�6]   .@�5   
   �� -   5        $��
Книги��5      .��5      � ���	#FFE5E5E5 � ColumnDefinitions 5      �� 5      $	��16* �6'   �� 5      $	��52* �6'   �� 5      $
��337* �6'   �� 5      $
��104* �6'   .+�5      )  #Microsoft.Windows.Controls.DataGrid  -   5          Name$ BooksDataGrid��5   E      AlternatingRowBackground �#EEEEEE   AutoGenerateColumns . $
��Left=�6�   $	��Top=�6�   $��3��6�   $	��293��6  $	��405��6  ��6�   �� 6  �� 5      -   5         ��Name$ 	AddButton��5      $��Добавить��6,   $��3��6?   $
��Left=�6O   $��5,29,0,0q�6j   $	��Top=�6|   $��89��6�   $��23��6�   6�   �� 5      -   5        $ 
EditButton��5      $��Изменить��6-   $��3��6@   $
��Left=�6P   $��5,69,0,0q�6k   $	��Top=�6}   $��89��6�   $��22��6�   6�   �� 5      -   5        $ DeleteButton��5      $$��Удалить
Удалить��6/   $��3��6R   $
��Left=�6b   $��	5,110,0,0q�6}   $	��Top=�6�   $��89��6�   $��19��6�   6�   5      5      �� 5   
   -   5        $��Издательства��5      .��5      � ���	#FFE5E5E5$	��295��6*   $	��Top=�67   $��	0,0,10,-2q�6O    5      �� 5      $	��31* �6'   �� 5      $	��60* �6'   .+�5!        -   5        $��PublishDataGrid��5!   E    �#EEEEEE .    CanUserAddRows .    CanUserDeleteRows . $
��Left=�6�   $��0,10,0,0q�6�   $	��Top=�6�   $��2��6  $	��285��6  $	��499��6$  ��6w   �� 6�  5#      5$      �� 5%   
   -	   5        $��Авторы��5%      .��5&      � ���	#FFE5E5E5$	��295��6*   $	��Top=�67   $��-1,-1,-5,-2q�6O   	 J� RenderTransformOrigin$	 0.5,0.5&�6d    5'      �� 5(      $	��93* �6'   �� 5)      $
��422* �6'   z�5+      V� 5,      .~�5-      �� �� 5.      �� 5/      
 �� Angle$
 0.292Q�6*   T� 50      51      .+�53        -
   5        $��AuthorsDataGrid��53   E    �#EEEEEE .  .  . $
��Left=�6(  $	��Top=�6C  $	��295��6[  $	��515��6h  $��2��6�  ��6�   �� 6�  54      55      56      57      