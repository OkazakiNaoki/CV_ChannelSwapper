#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "custom_cv_func.h"
#include <iostream>
#include <exception>
#include <vector>

namespace TextureLayerSwapper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	cv::Mat src;
	cv::Mat output;
	std::string srcFileName;
	std::vector<std::string> filesVec;
	int highestPercentageReached = 0;
	
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			InitializeBackgroundWorker();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private: System::Windows::Forms::PictureBox^ srcPicture;
	private: System::Windows::Forms::PictureBox^ outPicture;
	private: System::Windows::Forms::Label^ srcImgLbl;
	private: System::Windows::Forms::Label^ outImgLbl;
	private: System::Windows::Forms::Button^ browseBtn;
	private: System::Windows::Forms::Button^ processBtn;
	private: System::Windows::Forms::Button^ saveImgBtn;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ fixRedNrmRadBtn;
	private: System::Windows::Forms::RadioButton^ getRgbRadBtn;
	private: System::Windows::Forms::RadioButton^ getAlphaRadBtn;
	private: System::Windows::Forms::TabControl^ modeTabCon;
	private: System::Windows::Forms::TabPage^ singleImgPg;
	private: System::Windows::Forms::TabPage^ batchImgPg;
	private: System::Windows::Forms::Button^ browseSrcFdrBtn;



	private: System::Windows::Forms::Label^ fileListLbl;
	private: System::Windows::Forms::Label^ outFolderLbl;
	private: System::Windows::Forms::TextBox^ outFolderTbox;



	private: System::Windows::Forms::Button^ browseOutFdrBtn;

	private: System::Windows::Forms::Label^ srcFolderLbl;
	private: System::Windows::Forms::TextBox^ srcFolderTbox;
	private: System::Windows::Forms::Button^ batchProcBtn;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::ListBox^ fileListBox;
	private: System::Windows::Forms::Button^ resetFileListBtn;
	private: System::Windows::Forms::Button^ filterBtn;
	private: System::Windows::Forms::TextBox^ filterTbox;
	private: System::Windows::Forms::Label^ procStatusLbl;
	private: System::Windows::Forms::ProgressBar^ procProgBar;
	private: System::Windows::Forms::PictureBox^ loadingImgBox;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ abortProcBtn;






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeBackgroundWorker() {
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew DoWorkEventHandler(this, &MainForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerCompleted +=	gcnew RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorker1_RunWorkerCompleted);
			this->backgroundWorker1->ProgressChanged += gcnew ProgressChangedEventHandler(this, &MainForm::backgroundWorker1_ProgressChanged);
		}
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->srcPicture = (gcnew System::Windows::Forms::PictureBox());
			this->outPicture = (gcnew System::Windows::Forms::PictureBox());
			this->srcImgLbl = (gcnew System::Windows::Forms::Label());
			this->outImgLbl = (gcnew System::Windows::Forms::Label());
			this->browseBtn = (gcnew System::Windows::Forms::Button());
			this->processBtn = (gcnew System::Windows::Forms::Button());
			this->saveImgBtn = (gcnew System::Windows::Forms::Button());
			this->fixRedNrmRadBtn = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->getAlphaRadBtn = (gcnew System::Windows::Forms::RadioButton());
			this->getRgbRadBtn = (gcnew System::Windows::Forms::RadioButton());
			this->modeTabCon = (gcnew System::Windows::Forms::TabControl());
			this->singleImgPg = (gcnew System::Windows::Forms::TabPage());
			this->batchImgPg = (gcnew System::Windows::Forms::TabPage());
			this->abortProcBtn = (gcnew System::Windows::Forms::Button());
			this->loadingImgBox = (gcnew System::Windows::Forms::PictureBox());
			this->procStatusLbl = (gcnew System::Windows::Forms::Label());
			this->procProgBar = (gcnew System::Windows::Forms::ProgressBar());
			this->resetFileListBtn = (gcnew System::Windows::Forms::Button());
			this->filterBtn = (gcnew System::Windows::Forms::Button());
			this->filterTbox = (gcnew System::Windows::Forms::TextBox());
			this->fileListBox = (gcnew System::Windows::Forms::ListBox());
			this->batchProcBtn = (gcnew System::Windows::Forms::Button());
			this->outFolderLbl = (gcnew System::Windows::Forms::Label());
			this->outFolderTbox = (gcnew System::Windows::Forms::TextBox());
			this->browseOutFdrBtn = (gcnew System::Windows::Forms::Button());
			this->srcFolderLbl = (gcnew System::Windows::Forms::Label());
			this->srcFolderTbox = (gcnew System::Windows::Forms::TextBox());
			this->fileListLbl = (gcnew System::Windows::Forms::Label());
			this->browseSrcFdrBtn = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->srcPicture))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->outPicture))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->modeTabCon->SuspendLayout();
			this->singleImgPg->SuspendLayout();
			this->batchImgPg->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->loadingImgBox))->BeginInit();
			this->SuspendLayout();
			// 
			// srcPicture
			// 
			this->srcPicture->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->srcPicture->Location = System::Drawing::Point(20, 142);
			this->srcPicture->Name = L"srcPicture";
			this->srcPicture->Size = System::Drawing::Size(500, 500);
			this->srcPicture->TabIndex = 0;
			this->srcPicture->TabStop = false;
			// 
			// outPicture
			// 
			this->outPicture->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->outPicture->Location = System::Drawing::Point(555, 142);
			this->outPicture->Name = L"outPicture";
			this->outPicture->Size = System::Drawing::Size(500, 500);
			this->outPicture->TabIndex = 1;
			this->outPicture->TabStop = false;
			// 
			// srcImgLbl
			// 
			this->srcImgLbl->AutoSize = true;
			this->srcImgLbl->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->srcImgLbl->Location = System::Drawing::Point(15, 113);
			this->srcImgLbl->Name = L"srcImgLbl";
			this->srcImgLbl->Size = System::Drawing::Size(127, 26);
			this->srcImgLbl->TabIndex = 2;
			this->srcImgLbl->Text = L"Source image";
			// 
			// outImgLbl
			// 
			this->outImgLbl->AutoSize = true;
			this->outImgLbl->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outImgLbl->Location = System::Drawing::Point(550, 113);
			this->outImgLbl->Name = L"outImgLbl";
			this->outImgLbl->Size = System::Drawing::Size(121, 26);
			this->outImgLbl->TabIndex = 3;
			this->outImgLbl->Text = L"Result image";
			// 
			// browseBtn
			// 
			this->browseBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 20));
			this->browseBtn->Location = System::Drawing::Point(19, 28);
			this->browseBtn->Name = L"browseBtn";
			this->browseBtn->Size = System::Drawing::Size(187, 60);
			this->browseBtn->TabIndex = 4;
			this->browseBtn->Text = L"Browse image";
			this->browseBtn->UseVisualStyleBackColor = true;
			this->browseBtn->Click += gcnew System::EventHandler(this, &MainForm::ClickBrowseImgBtn);
			// 
			// processBtn
			// 
			this->processBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 20));
			this->processBtn->Location = System::Drawing::Point(555, 28);
			this->processBtn->Name = L"processBtn";
			this->processBtn->Size = System::Drawing::Size(187, 60);
			this->processBtn->TabIndex = 5;
			this->processBtn->Text = L"Process";
			this->processBtn->UseVisualStyleBackColor = true;
			this->processBtn->Click += gcnew System::EventHandler(this, &MainForm::processBtn_Click);
			// 
			// saveImgBtn
			// 
			this->saveImgBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 20));
			this->saveImgBtn->Location = System::Drawing::Point(763, 28);
			this->saveImgBtn->Name = L"saveImgBtn";
			this->saveImgBtn->Size = System::Drawing::Size(187, 60);
			this->saveImgBtn->TabIndex = 6;
			this->saveImgBtn->Text = L"Save result";
			this->saveImgBtn->UseVisualStyleBackColor = true;
			this->saveImgBtn->Click += gcnew System::EventHandler(this, &MainForm::saveImgBtn_Click);
			// 
			// fixRedNrmRadBtn
			// 
			this->fixRedNrmRadBtn->AutoSize = true;
			this->fixRedNrmRadBtn->Checked = true;
			this->fixRedNrmRadBtn->Location = System::Drawing::Point(17, 37);
			this->fixRedNrmRadBtn->Name = L"fixRedNrmRadBtn";
			this->fixRedNrmRadBtn->Size = System::Drawing::Size(119, 23);
			this->fixRedNrmRadBtn->TabIndex = 10;
			this->fixRedNrmRadBtn->TabStop = true;
			this->fixRedNrmRadBtn->Text = L"Fix red normal";
			this->fixRedNrmRadBtn->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->getAlphaRadBtn);
			this->groupBox1->Controls->Add(this->getRgbRadBtn);
			this->groupBox1->Controls->Add(this->fixRedNrmRadBtn);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(1090, 79);
			this->groupBox1->TabIndex = 11;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Channel swap options";
			// 
			// getAlphaRadBtn
			// 
			this->getAlphaRadBtn->AutoSize = true;
			this->getAlphaRadBtn->Location = System::Drawing::Point(260, 37);
			this->getAlphaRadBtn->Name = L"getAlphaRadBtn";
			this->getAlphaRadBtn->Size = System::Drawing::Size(121, 23);
			this->getAlphaRadBtn->TabIndex = 12;
			this->getAlphaRadBtn->Text = L"Get Alpha part";
			this->getAlphaRadBtn->UseVisualStyleBackColor = true;
			// 
			// getRgbRadBtn
			// 
			this->getRgbRadBtn->AutoSize = true;
			this->getRgbRadBtn->Location = System::Drawing::Point(142, 37);
			this->getRgbRadBtn->Name = L"getRgbRadBtn";
			this->getRgbRadBtn->Size = System::Drawing::Size(112, 23);
			this->getRgbRadBtn->TabIndex = 11;
			this->getRgbRadBtn->Text = L"Get RGB part";
			this->getRgbRadBtn->UseVisualStyleBackColor = true;
			// 
			// modeTabCon
			// 
			this->modeTabCon->Controls->Add(this->singleImgPg);
			this->modeTabCon->Controls->Add(this->batchImgPg);
			this->modeTabCon->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->modeTabCon->Location = System::Drawing::Point(12, 97);
			this->modeTabCon->Name = L"modeTabCon";
			this->modeTabCon->SelectedIndex = 0;
			this->modeTabCon->Size = System::Drawing::Size(1094, 690);
			this->modeTabCon->TabIndex = 12;
			// 
			// singleImgPg
			// 
			this->singleImgPg->Controls->Add(this->srcImgLbl);
			this->singleImgPg->Controls->Add(this->saveImgBtn);
			this->singleImgPg->Controls->Add(this->srcPicture);
			this->singleImgPg->Controls->Add(this->processBtn);
			this->singleImgPg->Controls->Add(this->browseBtn);
			this->singleImgPg->Controls->Add(this->outPicture);
			this->singleImgPg->Controls->Add(this->outImgLbl);
			this->singleImgPg->Location = System::Drawing::Point(4, 28);
			this->singleImgPg->Name = L"singleImgPg";
			this->singleImgPg->Padding = System::Windows::Forms::Padding(3);
			this->singleImgPg->Size = System::Drawing::Size(1086, 658);
			this->singleImgPg->TabIndex = 0;
			this->singleImgPg->Text = L"Single";
			this->singleImgPg->UseVisualStyleBackColor = true;
			// 
			// batchImgPg
			// 
			this->batchImgPg->Controls->Add(this->abortProcBtn);
			this->batchImgPg->Controls->Add(this->loadingImgBox);
			this->batchImgPg->Controls->Add(this->procStatusLbl);
			this->batchImgPg->Controls->Add(this->procProgBar);
			this->batchImgPg->Controls->Add(this->resetFileListBtn);
			this->batchImgPg->Controls->Add(this->filterBtn);
			this->batchImgPg->Controls->Add(this->filterTbox);
			this->batchImgPg->Controls->Add(this->fileListBox);
			this->batchImgPg->Controls->Add(this->batchProcBtn);
			this->batchImgPg->Controls->Add(this->outFolderLbl);
			this->batchImgPg->Controls->Add(this->outFolderTbox);
			this->batchImgPg->Controls->Add(this->browseOutFdrBtn);
			this->batchImgPg->Controls->Add(this->srcFolderLbl);
			this->batchImgPg->Controls->Add(this->srcFolderTbox);
			this->batchImgPg->Controls->Add(this->fileListLbl);
			this->batchImgPg->Controls->Add(this->browseSrcFdrBtn);
			this->batchImgPg->Location = System::Drawing::Point(4, 28);
			this->batchImgPg->Name = L"batchImgPg";
			this->batchImgPg->Padding = System::Windows::Forms::Padding(3);
			this->batchImgPg->Size = System::Drawing::Size(1086, 658);
			this->batchImgPg->TabIndex = 1;
			this->batchImgPg->Text = L"Batch";
			this->batchImgPg->UseVisualStyleBackColor = true;
			// 
			// abortProcBtn
			// 
			this->abortProcBtn->Enabled = false;
			this->abortProcBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 20));
			this->abortProcBtn->Location = System::Drawing::Point(402, 480);
			this->abortProcBtn->Name = L"abortProcBtn";
			this->abortProcBtn->Size = System::Drawing::Size(217, 60);
			this->abortProcBtn->TabIndex = 22;
			this->abortProcBtn->Text = L"Abort process";
			this->abortProcBtn->UseVisualStyleBackColor = true;
			this->abortProcBtn->Click += gcnew System::EventHandler(this, &MainForm::abortProcBtn_Click);
			// 
			// loadingImgBox
			// 
			this->loadingImgBox->Location = System::Drawing::Point(37, 593);
			this->loadingImgBox->Name = L"loadingImgBox";
			this->loadingImgBox->Size = System::Drawing::Size(55, 55);
			this->loadingImgBox->TabIndex = 21;
			this->loadingImgBox->TabStop = false;
			this->loadingImgBox->WaitOnLoad = true;
			// 
			// procStatusLbl
			// 
			this->procStatusLbl->AutoSize = true;
			this->procStatusLbl->Location = System::Drawing::Point(98, 593);
			this->procStatusLbl->Name = L"procStatusLbl";
			this->procStatusLbl->Size = System::Drawing::Size(53, 19);
			this->procStatusLbl->TabIndex = 20;
			this->procStatusLbl->Text = L"Status:";
			// 
			// procProgBar
			// 
			this->procProgBar->Location = System::Drawing::Point(13, 564);
			this->procProgBar->Name = L"procProgBar";
			this->procProgBar->Size = System::Drawing::Size(606, 23);
			this->procProgBar->TabIndex = 19;
			// 
			// resetFileListBtn
			// 
			this->resetFileListBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetFileListBtn->Location = System::Drawing::Point(983, 35);
			this->resetFileListBtn->Name = L"resetFileListBtn";
			this->resetFileListBtn->Size = System::Drawing::Size(75, 27);
			this->resetFileListBtn->TabIndex = 18;
			this->resetFileListBtn->Text = L"Reset";
			this->resetFileListBtn->UseVisualStyleBackColor = true;
			this->resetFileListBtn->Click += gcnew System::EventHandler(this, &MainForm::resetFileListBtn_Click);
			// 
			// filterBtn
			// 
			this->filterBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->filterBtn->Location = System::Drawing::Point(902, 35);
			this->filterBtn->Name = L"filterBtn";
			this->filterBtn->Size = System::Drawing::Size(75, 27);
			this->filterBtn->TabIndex = 17;
			this->filterBtn->Text = L"Filter";
			this->filterBtn->UseVisualStyleBackColor = true;
			this->filterBtn->Click += gcnew System::EventHandler(this, &MainForm::filterBtn_Click);
			// 
			// filterTbox
			// 
			this->filterTbox->Location = System::Drawing::Point(656, 35);
			this->filterTbox->Name = L"filterTbox";
			this->filterTbox->Size = System::Drawing::Size(240, 27);
			this->filterTbox->TabIndex = 16;
			// 
			// fileListBox
			// 
			this->fileListBox->FormattingEnabled = true;
			this->fileListBox->ItemHeight = 19;
			this->fileListBox->Location = System::Drawing::Point(656, 94);
			this->fileListBox->Name = L"fileListBox";
			this->fileListBox->Size = System::Drawing::Size(402, 536);
			this->fileListBox->TabIndex = 15;
			// 
			// batchProcBtn
			// 
			this->batchProcBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 20));
			this->batchProcBtn->Location = System::Drawing::Point(13, 480);
			this->batchProcBtn->Name = L"batchProcBtn";
			this->batchProcBtn->Size = System::Drawing::Size(373, 60);
			this->batchProcBtn->TabIndex = 14;
			this->batchProcBtn->Text = L"Batch process";
			this->batchProcBtn->UseVisualStyleBackColor = true;
			this->batchProcBtn->Click += gcnew System::EventHandler(this, &MainForm::batchProcBtn_Click);
			// 
			// outFolderLbl
			// 
			this->outFolderLbl->AutoSize = true;
			this->outFolderLbl->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outFolderLbl->Location = System::Drawing::Point(8, 347);
			this->outFolderLbl->Name = L"outFolderLbl";
			this->outFolderLbl->Size = System::Drawing::Size(172, 26);
			this->outFolderLbl->TabIndex = 13;
			this->outFolderLbl->Text = L"Output folder path";
			// 
			// outFolderTbox
			// 
			this->outFolderTbox->Location = System::Drawing::Point(13, 374);
			this->outFolderTbox->Name = L"outFolderTbox";
			this->outFolderTbox->ReadOnly = true;
			this->outFolderTbox->Size = System::Drawing::Size(606, 27);
			this->outFolderTbox->TabIndex = 12;
			// 
			// browseOutFdrBtn
			// 
			this->browseOutFdrBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 20));
			this->browseOutFdrBtn->Location = System::Drawing::Point(13, 275);
			this->browseOutFdrBtn->Name = L"browseOutFdrBtn";
			this->browseOutFdrBtn->Size = System::Drawing::Size(373, 60);
			this->browseOutFdrBtn->TabIndex = 11;
			this->browseOutFdrBtn->Text = L"Browse output folder";
			this->browseOutFdrBtn->UseVisualStyleBackColor = true;
			this->browseOutFdrBtn->Click += gcnew System::EventHandler(this, &MainForm::browseOutFdrBtn_Click);
			// 
			// srcFolderLbl
			// 
			this->srcFolderLbl->AutoSize = true;
			this->srcFolderLbl->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->srcFolderLbl->Location = System::Drawing::Point(8, 148);
			this->srcFolderLbl->Name = L"srcFolderLbl";
			this->srcFolderLbl->Size = System::Drawing::Size(158, 26);
			this->srcFolderLbl->TabIndex = 10;
			this->srcFolderLbl->Text = L"Sorce folder path";
			// 
			// srcFolderTbox
			// 
			this->srcFolderTbox->Location = System::Drawing::Point(13, 175);
			this->srcFolderTbox->Name = L"srcFolderTbox";
			this->srcFolderTbox->ReadOnly = true;
			this->srcFolderTbox->Size = System::Drawing::Size(606, 27);
			this->srcFolderTbox->TabIndex = 9;
			// 
			// fileListLbl
			// 
			this->fileListLbl->AutoSize = true;
			this->fileListLbl->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fileListLbl->Location = System::Drawing::Point(651, 71);
			this->fileListLbl->Name = L"fileListLbl";
			this->fileListLbl->Size = System::Drawing::Size(72, 26);
			this->fileListLbl->TabIndex = 8;
			this->fileListLbl->Text = L"File list";
			// 
			// browseSrcFdrBtn
			// 
			this->browseSrcFdrBtn->Font = (gcnew System::Drawing::Font(L"Calibri", 20));
			this->browseSrcFdrBtn->Location = System::Drawing::Point(13, 76);
			this->browseSrcFdrBtn->Name = L"browseSrcFdrBtn";
			this->browseSrcFdrBtn->Size = System::Drawing::Size(373, 60);
			this->browseSrcFdrBtn->TabIndex = 7;
			this->browseSrcFdrBtn->Text = L"Browse source folder";
			this->browseSrcFdrBtn->UseVisualStyleBackColor = true;
			this->browseSrcFdrBtn->Click += gcnew System::EventHandler(this, &MainForm::browseFolderBtn_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1120, 794);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->modeTabCon);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"Texture channel swapper";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->srcPicture))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->outPicture))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->modeTabCon->ResumeLayout(false);
			this->singleImgPg->ResumeLayout(false);
			this->singleImgPg->PerformLayout();
			this->batchImgPg->ResumeLayout(false);
			this->batchImgPg->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->loadingImgBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ClickBrowseImgBtn(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ dgOpen = gcnew OpenFileDialog();
		dgOpen->Filter = "Targa image(*.tga)|*.tga|All files (*.*)|*.*||";
		if (dgOpen->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}

		// draw bitmap
		if (this->srcPicture->Image)
			delete this->srcPicture->Image;
		this->srcPicture->Image = gcnew Bitmap(GenerateTempSrcPNG(dgOpen->FileName));
		this->srcPicture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->srcPicture->Refresh();

		ReadImageIntoMat(ConvertString2Char(dgOpen->FileName), src);
	}
	private: void ReadImageIntoMat(std::string filePath, cv::Mat& mat) {
		// release mem first
		free(mat.data);
		mat.release();
		// load image data
		int texW, texH, nrChannels;
		srcFileName = GetFileNameFromPath(filePath);
		uchar* data = stbi_load(filePath.c_str(), &texW, &texH, &nrChannels, 0);

		mat = cv::Mat(texH, texW, CV_8UC(nrChannels), data);
	}
	private: std::string GetFileNameFromPath(std::string const& path)
	{
		return path.substr(path.find_last_of("/\\") + 1);
	}

	private: char* ConvertString2Char(System::String^ str)
	{	//Marshal method
		char* str2 = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
		return str2;
	}

	private: System::String^ GenerateTempSrcPNG(System::String^ filePath)
	{
		int texW, texH, nrChannels;
		uchar* data = stbi_load(ConvertString2Char(filePath), &texW, &texH, &nrChannels, 0);
		stbi_write_png_compression_level = 0;
		stbi_write_png("img_cache\\tempSrc.png", texW, texH, nrChannels, data, texW * nrChannels);
		delete[] data;
		return L"img_cache\\tempSrc.png";
	}
	private: System::Void processBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (src.empty() || (!fixRedNrmRadBtn->Checked && !getRgbRadBtn->Checked && !getAlphaRadBtn->Checked))
			return;
		else if (fixRedNrmRadBtn->Checked)
			NormalFixer(src, output);
		else if (getRgbRadBtn->Checked)
			GetRGBpart(src, output);
		else if (getAlphaRadBtn->Checked)
			GetAlphaPart(src, output);
		
		if (outPicture->Image)
			delete outPicture->Image;
		Bitmap^ bmpSrc = gcnew Bitmap(GenerateTempOutPNG());
		outPicture->Image = bmpSrc;
		outPicture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		outPicture->Refresh();
	}
	private: System::String^ GenerateTempOutPNG()
	{
		stbi_write_png_compression_level = 0;
		stbi_write_png("img_cache\\tempOut.png", output.size().width, output.size().height, output.channels(), output.data, output.size().width * output.channels());
		return L"img_cache\\tempOut.png";
	}
	private: System::Void saveImgBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!output.empty()) {
			SaveFileDialog^ saveFile = gcnew SaveFileDialog();
			saveFile->FileName = gcnew String(srcFileName.c_str());
			saveFile->DefaultExt = "tga";
			saveFile->Filter = "Targa image(*.tga)|*.tga|All files (*.*)|*.*||";
			if (saveFile->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				stbi_write_tga_with_rle = 0;
				stbi_write_tga(ConvertString2Char(saveFile->FileName), output.size().width, output.size().height, output.channels(), output.data);
			}
		}
	}
	private: System::Void browseFolderBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			srcFolderTbox->Text = folderBrowserDialog1->SelectedPath;
			GetFileListFromPath(folderBrowserDialog1->SelectedPath, true);
		}
	}
	private: void GetFileListFromPath(String^ path, bool newCreated) {
		fileListBox->Items->Clear();
		if (newCreated)
			filesVec.clear();
		cli::array<System::String^>^ fileArray = System::IO::Directory::GetFiles(path);
		String^ fileTypeFilter = gcnew String(".tga");
		for each (String^ f in fileArray)
		{
			if (f->Contains(fileTypeFilter)) {
				if (newCreated)
					filesVec.push_back(GetFileNameFromPath(ConvertString2Char(f)));
				String^ fileName = gcnew String(GetFileNameFromPath(ConvertString2Char(f)).c_str());
				fileListBox->Items->Add(fileName);
				delete fileName;
			}
		}
		delete fileTypeFilter;
	}
	private: System::Void browseOutFdrBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			outFolderTbox->Text = folderBrowserDialog1->SelectedPath;
		}
	}
	private: System::Void filterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		fileListBox->Items->Clear();
		std::string filterStr = ConvertString2Char(filterTbox->Text);
		for (size_t i = 0; i < filesVec.size(); i++) {
			if (filesVec[i].find(filterStr) != std::string::npos) {
				String^ fileName = gcnew String(GetFileNameFromPath(filesVec[i]).c_str());
				fileListBox->Items->Add(fileName);
				delete fileName;
			}
		}
	}
	private: System::Void resetFileListBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!this->srcFolderTbox->Text->Equals(""))
			GetFileListFromPath(this->srcFolderTbox->Text, false);
	}
	private: System::Void batchProcBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->fileListBox->Items->Count == 0 || this->srcFolderTbox->Text->Equals("") || this->outFolderTbox->Text->Equals(""))
			return;
		else if (!this->fixRedNrmRadBtn->Checked && !this->getRgbRadBtn->Checked && !this->getAlphaRadBtn->Checked)
			return;

		highestPercentageReached = 0;
		this->procStatusLbl->Text = L"Status: processing...";
		this->procStatusLbl->Refresh();
		SetLoadingPicture(L"icons\\heavy_load.gif");
		this->batchProcBtn->Enabled = false;
		this->abortProcBtn->Enabled = true;


		this->backgroundWorker1->RunWorkerAsync(this->fileListBox->Items->Count);
	}
	private: void ProcessImage(int listSize, BackgroundWorker^ worker, DoWorkEventArgs^ e) {
		for (int i = 0; i < listSize; i++) {
			std::string importPath = ConvertString2Char(this->srcFolderTbox->Text + "\\" + this->fileListBox->Items[i]->ToString());
			std::string exportPath = ConvertString2Char(this->outFolderTbox->Text + "\\" + this->fileListBox->Items[i]->ToString());
			cv::Mat in;
			cv::Mat out;
			ReadImageIntoMat(importPath, in);
			if (this->fixRedNrmRadBtn->Checked)
				NormalFixer(in, out);
			else if (this->getRgbRadBtn->Checked)
				GetRGBpart(in, out);
			else if (this->getAlphaRadBtn->Checked)
				GetAlphaPart(in, out);

			stbi_write_tga_with_rle = 0;
			stbi_write_tga(exportPath.c_str(), out.size().width, out.size().height, out.channels(), out.data);
			free(in.data);
			in.release();
			out.release();
			if (worker->CancellationPending)
			{
				e->Cancel = true;
			}
			else {
				int percentComplete = (int)((float)(i + 1) / (float)listSize * 100);
				if (percentComplete > highestPercentageReached)
				{
					highestPercentageReached = percentComplete;
					worker->ReportProgress(percentComplete);
				}
			}
		}
	}
	private: void SetLoadingPicture(String^ imgName) {
		this->loadingImgBox->Image = gcnew Bitmap(imgName);
		this->loadingImgBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		this->loadingImgBox->Refresh();
	}
	private: void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
	{
		BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);
		ProcessImage(static_cast<int>(e->Argument), worker, e);
	}
	private: void backgroundWorker1_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
		this->procProgBar->Value = e->ProgressPercentage;
	}
	private: void backgroundWorker1_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
		if (e->Cancelled) {
			this->procStatusLbl->Text = L"mission failed we'll get em next time";
			this->procStatusLbl->Refresh();
			SetLoadingPicture(L"icons\\ree.gif");
		}
		else if (e->Error != nullptr) {
			this->procStatusLbl->Text = L"error: " + e->Error->Message;
			this->procStatusLbl->Refresh();
			std::cout << ConvertString2Char(e->Error->Message) << std::endl;
		}
		else {
			this->procStatusLbl->Text = L"status: finished process!";
			this->procStatusLbl->Refresh();
			SetLoadingPicture(L"icons\\ADADAD.gif");
		}
		this->batchProcBtn->Enabled = true;
		this->abortProcBtn->Enabled = false;
		this->procStatusLbl->Refresh();
	}
	private: System::Void abortProcBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		this->backgroundWorker1->CancelAsync();
		this->procStatusLbl->Text = L"status: aborting...";
		this->procStatusLbl->Refresh();
	}
};
}
