// projet.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include "gui.h"


ButtonBox::ButtonBox(	bool horizontal, const Glib::ustring& title,
									gint spacing,  Gtk::ButtonBoxStyle layout)
: 	Gtk::Frame(title),
	m_Button_Exit("Exit"),
	m_Button_Start("Open"),
	m_Button_Open("Save"),
	m_Button_Step("Start"),
	m_Button_Save("Step")
{
	Gtk::ButtonBox* bbox = nullptr;

	bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );

	bbox->set_border_width(5);

	add(*bbox);

	/* Set the appearance of the Button Box */
	bbox->set_layout(layout);
	bbox->set_spacing(5);
	bbox->add(m_Button_Exit);
	bbox->add(m_Button_Start);
	bbox->add(m_Button_Open);
	bbox->add(m_Button_Step);
	bbox->add(m_Button_Save);
}

ButtonBox2::ButtonBox2(	bool horizontal, const Glib::ustring& title,
									gint spacing,  Gtk::ButtonBoxStyle layout)
: 	Gtk::Frame(title),
	m_Button_Link("Toggle link"),
	m_Button_Range("Toggle range")
{
	Gtk::ButtonBox* bbox2 = nullptr;

	bbox2 = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );

	bbox2->set_border_width(5);

	add(*bbox2);

	/* Set the appearance of the Button Box */
	bbox2->set_layout(layout);
	bbox2->set_spacing(2);
	bbox2->add(m_Button_Link);
	bbox2->add(m_Button_Range);

}


Window::Window()
: 	m_box(Gtk::ORIENTATION_VERTICAL),
	m_box_Bottom(Gtk::ORIENTATION_VERTICAL,5),
	m_box_Top(Gtk::ORIENTATION_HORIZONTAL,5),
	m_box_Button(Gtk::ORIENTATION_VERTICAL,5)
{
	set_title("Planet Donut");
	add(m_box);
	m_box.set_border_width(5);
	m_box.add(m_box_Top);
	m_box.add(m_box_Bottom);
	m_box_Top.add(m_box_Button);
	m_box_Button.add(m_box_General);
	m_box_Button.add(m_box_Display);
	//Scroll scroll;
	//m_box_Bottom.add(scroll);
	
  //The vertical ButtonBoxes:

			
	m_box_General.pack_start(	*Gtk::manage( new ButtonBox(false, "General", 5,
			Gtk::BUTTONBOX_SPREAD)), Gtk::PACK_EXPAND_WIDGET);
			
	m_box_Display.pack_start(*Gtk::manage( new ButtonBox2(false, "Toggle Display", 5,
			Gtk::BUTTONBOX_SPREAD)), Gtk::PACK_EXPAND_WIDGET);

	//m_box_Top.pack_start(m_box, Gtk::PACK_EXPAND_WIDGET);
	
//	m_box_Bottom.pack_start()


  show_all_children();
}

Window::~Window()
{
}

void Window::on_button_clicked()
{
  hide();
}

