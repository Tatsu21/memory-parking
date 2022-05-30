#pragma once
#include "memoryparking.h";
#include <msclr\marshal_cppstd.h>

namespace memoryparking {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}



	private: System::Windows::Forms::ToolStripMenuItem^ featureToolStripMenuItem;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ akazeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ kazeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ siftToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ oRBToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ matchingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ bRUTEFORCEToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ fLANNToolStripMenuItem;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::Button^ button1;


	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::DirectoryServices::DirectoryEntry^ directoryEntry1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::TextBox^ textBox12;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;




	protected:









	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->featureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->akazeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kazeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->siftToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->oRBToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->matchingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bRUTEFORCEToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fLANNToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog2 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->directoryEntry1 = (gcnew System::DirectoryServices::DirectoryEntry());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// featureToolStripMenuItem
			// 
			this->featureToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->akazeToolStripMenuItem,
					this->kazeToolStripMenuItem, this->siftToolStripMenuItem, this->oRBToolStripMenuItem
			});
			this->featureToolStripMenuItem->Name = L"featureToolStripMenuItem";
			this->featureToolStripMenuItem->Size = System::Drawing::Size(72, 24);
			this->featureToolStripMenuItem->Text = L"Feature";
			// 
			// akazeToolStripMenuItem
			// 
			this->akazeToolStripMenuItem->Name = L"akazeToolStripMenuItem";
			this->akazeToolStripMenuItem->Size = System::Drawing::Size(138, 26);
			this->akazeToolStripMenuItem->Text = L"A-kaze";
			this->akazeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::akazeToolStripMenuItem_Click);
			// 
			// kazeToolStripMenuItem
			// 
			this->kazeToolStripMenuItem->Name = L"kazeToolStripMenuItem";
			this->kazeToolStripMenuItem->Size = System::Drawing::Size(138, 26);
			this->kazeToolStripMenuItem->Text = L"Kaze";
			this->kazeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kazeToolStripMenuItem_Click);
			// 
			// siftToolStripMenuItem
			// 
			this->siftToolStripMenuItem->Name = L"siftToolStripMenuItem";
			this->siftToolStripMenuItem->Size = System::Drawing::Size(138, 26);
			this->siftToolStripMenuItem->Text = L"Sift";
			this->siftToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::siftToolStripMenuItem_Click);
			// 
			// oRBToolStripMenuItem
			// 
			this->oRBToolStripMenuItem->Name = L"oRBToolStripMenuItem";
			this->oRBToolStripMenuItem->Size = System::Drawing::Size(138, 26);
			this->oRBToolStripMenuItem->Text = L"ORB";
			this->oRBToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::oRBToolStripMenuItem_Click);
			// 
			// matchingToolStripMenuItem
			// 
			this->matchingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->bRUTEFORCEToolStripMenuItem,
					this->fLANNToolStripMenuItem
			});
			this->matchingToolStripMenuItem->Name = L"matchingToolStripMenuItem";
			this->matchingToolStripMenuItem->Size = System::Drawing::Size(85, 24);
			this->matchingToolStripMenuItem->Text = L"Matching";
			// 
			// bRUTEFORCEToolStripMenuItem
			// 
			this->bRUTEFORCEToolStripMenuItem->Name = L"bRUTEFORCEToolStripMenuItem";
			this->bRUTEFORCEToolStripMenuItem->Size = System::Drawing::Size(180, 26);
			this->bRUTEFORCEToolStripMenuItem->Text = L"BRUTEFORCE";
			// 
			// fLANNToolStripMenuItem
			// 
			this->fLANNToolStripMenuItem->Name = L"fLANNToolStripMenuItem";
			this->fLANNToolStripMenuItem->Size = System::Drawing::Size(180, 26);
			this->fLANNToolStripMenuItem->Text = L"FLANN";
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->featureToolStripMenuItem,
					this->matchingToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1279, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(88)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button1->Location = System::Drawing::Point(16, 47);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 33);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Open Image";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button1_MouseClick);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(88)),
				static_cast<System::Int32>(static_cast<System::Byte>(166)));
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button2->Location = System::Drawing::Point(481, 48);
			this->button2->Margin = System::Windows::Forms::Padding(4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(117, 32);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Select dataset";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(16, 89);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(425, 356);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(76)), static_cast<System::Int32>(static_cast<System::Byte>(53)),
				static_cast<System::Int32>(static_cast<System::Byte>(117)));
			this->listView1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(76)), static_cast<System::Int32>(static_cast<System::Byte>(53)),
				static_cast<System::Int32>(static_cast<System::Byte>(117)));
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(481, 96);
			this->listView1->Margin = System::Windows::Forms::Padding(4);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(185, 349);
			this->listView1->TabIndex = 4;
			this->listView1->UseCompatibleStateImageBehavior = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(827, 89);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(436, 356);
			this->pictureBox2->TabIndex = 5;
			this->pictureBox2->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label1->Location = System::Drawing::Point(824, 56);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 17);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Result";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(16, 487);
			this->textBox1->Margin = System::Windows::Forms::Padding(4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(128, 22);
			this->textBox1->TabIndex = 7;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(16, 540);
			this->textBox2->Margin = System::Windows::Forms::Padding(4);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(128, 22);
			this->textBox2->TabIndex = 8;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(172, 487);
			this->textBox3->Margin = System::Windows::Forms::Padding(4);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(128, 22);
			this->textBox3->TabIndex = 9;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(172, 540);
			this->textBox4->Margin = System::Windows::Forms::Padding(4);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(128, 22);
			this->textBox4->TabIndex = 10;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(325, 487);
			this->textBox5->Margin = System::Windows::Forms::Padding(4);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(128, 22);
			this->textBox5->TabIndex = 11;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(325, 540);
			this->textBox6->Margin = System::Windows::Forms::Padding(4);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(128, 22);
			this->textBox6->TabIndex = 12;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(481, 487);
			this->textBox7->Margin = System::Windows::Forms::Padding(4);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(128, 22);
			this->textBox7->TabIndex = 13;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(481, 540);
			this->textBox8->Margin = System::Windows::Forms::Padding(4);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(128, 22);
			this->textBox8->TabIndex = 14;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::White;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->button3->Location = System::Drawing::Point(1012, 498);
			this->button3->Margin = System::Windows::Forms::Padding(4);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(185, 54);
			this->button3->TabIndex = 15;
			this->button3->Text = L"Run";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(635, 487);
			this->textBox9->Margin = System::Windows::Forms::Padding(4);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(128, 22);
			this->textBox9->TabIndex = 16;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(635, 540);
			this->textBox10->Margin = System::Windows::Forms::Padding(4);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(128, 22);
			this->textBox10->TabIndex = 17;
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(784, 540);
			this->textBox11->Margin = System::Windows::Forms::Padding(4);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(128, 22);
			this->textBox11->TabIndex = 18;
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(784, 487);
			this->textBox12->Margin = System::Windows::Forms::Padding(4);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(128, 22);
			this->textBox12->TabIndex = 19;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::Color::Red;
			this->label2->Location = System::Drawing::Point(1010, 477);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(111, 17);
			this->label2->TabIndex = 20;
			this->label2->Text = L"Select a feature!";
			this->label2->UseWaitCursor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label3->Location = System::Drawing::Point(12, 466);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(46, 17);
			this->label3->TabIndex = 21;
			this->label3->Text = L"label3";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label4->Location = System::Drawing::Point(169, 466);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(46, 17);
			this->label4->TabIndex = 22;
			this->label4->Text = L"label4";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label5->Location = System::Drawing::Point(322, 466);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(46, 17);
			this->label5->TabIndex = 23;
			this->label5->Text = L"label5";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label6->Location = System::Drawing::Point(478, 466);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(46, 17);
			this->label6->TabIndex = 24;
			this->label6->Text = L"label6";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label7->Location = System::Drawing::Point(632, 466);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(46, 17);
			this->label7->TabIndex = 25;
			this->label7->Text = L"label7";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label8->Location = System::Drawing::Point(781, 466);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(46, 17);
			this->label8->TabIndex = 26;
			this->label8->Text = L"label8";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(46)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(73)));
			this->ClientSize = System::Drawing::Size(1279, 619);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox12);
			this->Controls->Add(this->textBox11);
			this->Controls->Add(this->textBox10);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:int featureSelect = 0;
	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "txt files (.jpg)|.jpg|All files (.)|.";
		openFileDialog1->FilterIndex = 1;
		openFileDialog1->RestoreDirectory = true;
	}
	private: System::Void button1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->InitialDirectory = "c:\\";

		openFileDialog1->RestoreDirectory = true;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			System::String^ path = openFileDialog1->FileName;
			pictureBox1->ImageLocation = path;

		}


	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void akazeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		featureSelect = 1;
		label3->Text = "Descriptor Size";
		label4->Text = "Descriptor Channels";
		label5->Text = "Threshold";
		label6->Text = "n Octave";
		label7->Text = "n Octave Layers";
	}
	private: System::Void kazeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		featureSelect = 2;
		label3->Text = "Extended";
		label4->Text = "Upright";
		label5->Text = "Threshold";
		label6->Text = "n Octave";
		label7->Text = "n Octave Layers";

	}
	private: System::Void siftToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		featureSelect = 3;
		label3->Text = "n Features";
		label4->Text = "n Octave Layers";
		label5->Text = "Contrast Threshold";
		label6->Text = "Edge Threshold";
		label7->Text = "Sigma";

	}
	private: System::Void oRBToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		featureSelect = 4;
		label3->Text = "Descriptor Size";
		label4->Text = "Descriptor Channels";
		label5->Text = "Threshold";
		label6->Text = "n Octave";
		label7->Text = "n Octave Layers";

	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {

		label2->Hide();
		if (featureSelect == 1)
		{
			int descSize = stoi(msclr::interop::marshal_as<std::string>(textBox1->Text));
			int descChan = stoi(msclr::interop::marshal_as<std::string>(textBox3->Text));
			float thresh = stof(msclr::interop::marshal_as<std::string>(textBox5->Text));
			int nOct = stoi(msclr::interop::marshal_as<std::string>(textBox7->Text));
			int nOctL = stoi(msclr::interop::marshal_as<std::string>(textBox9->Text));
			AKAZEMatching(descSize, descChan, thresh, nOct, nOctL);
		}
		if (featureSelect == 2) {
			bool ext = ((msclr::interop::marshal_as<std::string>(textBox1->Text))=="true");
			bool up = ((msclr::interop::marshal_as<std::string>(textBox3->Text))=="true");
			float thresh = stof(msclr::interop::marshal_as<std::string>(textBox5->Text));
			int nOct = stoi(msclr::interop::marshal_as<std::string>(textBox7->Text));
			int nOctL = stoi(msclr::interop::marshal_as<std::string>(textBox9->Text));
			KAZEMatching(ext, up, thresh, nOct, nOctL);
		}
		if (featureSelect == 3)
		{
			int nFeat = stoi(msclr::interop::marshal_as<std::string>(textBox1->Text));
			int nOctL = stoi(msclr::interop::marshal_as<std::string>(textBox3->Text));
			double contrThr = stod(msclr::interop::marshal_as<std::string>(textBox5->Text));
			double edgeThr = stod(msclr::interop::marshal_as<std::string>(textBox7->Text));
			double Sigma = stod(msclr::interop::marshal_as<std::string>(textBox9->Text));
			SIFTMatching(nFeat, nOctL, contrThr, edgeThr ,Sigma);
		}
		if (featureSelect == 4)
		{
			int descSize = stoi(msclr::interop::marshal_as<std::string>(textBox1->Text));
			int descChan = stoi(msclr::interop::marshal_as<std::string>(textBox3->Text));
			float thresh = stof(msclr::interop::marshal_as<std::string>(textBox5->Text));
			int nOct = stoi(msclr::interop::marshal_as<std::string>(textBox7->Text));
			int nOctL = stoi(msclr::interop::marshal_as<std::string>(textBox9->Text));
			ORBMatching(descSize, descChan, thresh, nOct, nOctL);
		}
	}
};
	
}