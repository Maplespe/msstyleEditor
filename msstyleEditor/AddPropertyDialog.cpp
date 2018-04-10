#include "AddPropertyDialog.h"
#include "libmsstyle\VisualStyleDefinitions.h"

using namespace libmsstyle;

const char* typeNameArray[] =
{
	"Enum",
	"Bool",
	"Color",
	"Margin"
};

const int typeIdArray[] =
{
	200,
	203,
	204,
	205
};

class wxPropertyClientData : public wxClientData
{
public:
	wxPropertyClientData() : m_data() { }
	wxPropertyClientData(const PropertyInfo &data) : m_data(data) { }
	void SetData(const PropertyInfo &data) { m_data = data; }
	const PropertyInfo& GetData() const { return m_data; }

private:
	PropertyInfo m_data;
};

AddPropertyDialog::AddPropertyDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(size, size);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText5 = new wxStaticText(this, wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText5->Wrap(-1);
	m_staticText5->SetMaxSize(wxSize(120, -1));
	bSizer16->Add(m_staticText5, 1, wxTOP | wxRIGHT | wxLEFT, 5);

	m_staticText6 = new wxStaticText(this, wxID_ANY, wxT("Property:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText6->Wrap(-1);
	bSizer16->Add(m_staticText6, 1, wxTOP | wxRIGHT | wxLEFT, 5);


	bSizer13->Add(bSizer16, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer(wxHORIZONTAL);

	wxArrayString typeBoxChoices;
	typeBoxChoices.Add(typeNameArray[0]);
	typeBoxChoices.Add(typeNameArray[1]);
	typeBoxChoices.Add(typeNameArray[2]);
	typeBoxChoices.Add(typeNameArray[3]);
	typeBox = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, typeBoxChoices, 0);
	typeBox->SetSelection(0);
	typeBox->SetMaxSize(wxSize(120, -1));

	bSizer14->Add(typeBox, 1, wxALL, 5);

	wxArrayString propBoxChoices;
	propBox = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, propBoxChoices, 0);
	propBox->SetSelection(0);
	bSizer14->Add(propBox, 1, wxALL, 5);


	bSizer13->Add(bSizer14, 0, wxEXPAND, 5);

	descriptionLabel = new wxStaticText(this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE);
	descriptionLabel->Wrap(300);
	bSizer13->Add(descriptionLabel, 1, wxALL | wxEXPAND, 5);

	m_staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer13->Add(m_staticLine, 0, wxEXPAND | wxTOP | wxRIGHT | wxLEFT, 5);

	okButton = new wxButton(this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer13->Add(okButton, 0, wxALL | wxALIGN_RIGHT, 5);


	this->SetSizer(bSizer13);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	typeBox->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(AddPropertyDialog::OnTypeSelectionChanged), NULL, this);
	propBox->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(AddPropertyDialog::OnPropertySelectionChanged), NULL, this);
	okButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddPropertyDialog::OnOkClicked), NULL, this);

	OnTypeSelectionChanged(wxCommandEvent());
}

void AddPropertyDialog::OnTypeSelectionChanged(wxCommandEvent& event)
{
	propBox->Clear();

	int selectedIndex = typeBox->GetSelection();
	if (selectedIndex < 0)
		return;

	int typeId = typeIdArray[selectedIndex];
	for (auto& it = PROPERTY_INFO_MAP.begin(); it != PROPERTY_INFO_MAP.end(); ++it)
	{
		if (typeId == it->second.type)
		{
			propBox->Append(it->second.name, new wxPropertyClientData(it->second));
		}
	}

	propBox->Select(0);
}

void AddPropertyDialog::OnPropertySelectionChanged(wxCommandEvent& event)
{
	int selectedIndex = propBox->GetSelection();
	if (selectedIndex < 0)
		return;

	wxPropertyClientData* cd = static_cast<wxPropertyClientData*>(propBox->GetClientObject(selectedIndex));
	descriptionLabel->SetLabel(wxString("Description: ") + cd->GetData().description);
}

void AddPropertyDialog::OnOkClicked(wxCommandEvent& event)
{
	event.Skip();
}

AddPropertyDialog::~AddPropertyDialog()
{
	// Disconnect Events
	typeBox->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(AddPropertyDialog::OnTypeSelectionChanged), NULL, this);
	propBox->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(AddPropertyDialog::OnPropertySelectionChanged), NULL, this);
	okButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddPropertyDialog::OnOkClicked), NULL, this);

}