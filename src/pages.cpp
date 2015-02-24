#include "pages.h"
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QColorDialog>
#include <QDebug>
#include <QSettings>
#include <QTextEdit>
#include <QFileDialog>
#include <QFontDialog>
#include <QPlainTextEdit>
#include "prefpage.h"
#include "QLineEdit"


void GeneralPage::load(){
   // qDebug() << settings.value("gen/dir").toString();
    dirEdit->setPlainText(settings.value("gen/dir").toString());
    adjustIntervalEdit->setText(settings.value("gen/adjust").toString());
}


void GeneralPage::save(){
    //qDebug() << "configsave";
    settings.setValue("gen/dir",dirEdit->toPlainText());
    settings.setValue("gen/adjust",adjustIntervalEdit->text());
}

void GeneralPage::openDirDialog(){
    QString path = QFileDialog::getExistingDirectory();
    if (!path.isNull()) dirEdit->setPlainText(path);
}

GeneralPage::GeneralPage(QWidget *parent)
    : PrefPage(parent)
{
    QGroupBox *filesGroup = new QGroupBox(tr("Files"));

    QGroupBox *adjustGroup = new QGroupBox(tr("Adjustment"));

    QLabel *defaultDirLabel = new QLabel(tr("Default Directory:"));
    dirEdit = new QPlainTextEdit();
    QPushButton *dirBrowseButton = new QPushButton(tr("Browse"));
    connect(dirBrowseButton, SIGNAL(clicked()), this, SLOT(openDirDialog()));

    QLabel *adjustIntervalLabel = new QLabel(tr("Time Adjustment Interval (ms): "));
    adjustIntervalEdit = new QLineEdit();
    adjustIntervalEdit->setMaxLength(9);
    adjustIntervalEdit->setValidator( new QIntValidator(0, MAX_ADJUST_INTERVAL, this) );

    QHBoxLayout *defaultDirLayout = new QHBoxLayout;
    defaultDirLayout->addWidget(defaultDirLabel);
    defaultDirLayout->addWidget(dirEdit);
    defaultDirLayout->addWidget(dirBrowseButton);

    QHBoxLayout *adjustIntervalLayout = new QHBoxLayout;
    adjustIntervalLayout->addWidget(adjustIntervalLabel);
    adjustIntervalLayout->addWidget(adjustIntervalEdit);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(defaultDirLayout);
    filesGroup->setLayout(configLayout);

    QVBoxLayout *adjustLayout = new QVBoxLayout;
    adjustLayout->addLayout(adjustIntervalLayout);
    adjustGroup->setLayout(adjustLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(filesGroup);
    mainLayout->addStretch(1);
    mainLayout->addWidget(adjustGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    this->load();
}

void AppearancePage::openColorDialog(){
    QColor color = QColorDialog::getColor (bgColor, 0, tr("Select Color"), QColorDialog::ShowAlphaChannel);
    if (color.isValid()){
        //QSettings settings;
        bgColor = color;
        qDebug() << color.rgba();
    }

}

void AppearancePage::load(){
    bgColor = QColor::fromRgba(settings.value("appearance/bgcolor").toUInt());
    fontLabel->setText(settings.value("appearance/font").toString());
}


void AppearancePage::save(){
    settings.setValue("appearance/font", fontLabel->text());
    settings.setValue("appearance/bgcolor", bgColor.rgba());
}

void AppearancePage::openFontDialog(){
    bool ok;
    QFont initial;
    initial.fromString(fontLabel->text());
    QFont font = QFontDialog::getFont(&ok, initial);
    if (ok){
        fontLabel->setText(font.toString());
    }
}

AppearancePage::~AppearancePage(){

}

AppearancePage::AppearancePage(QWidget *parent)
    : PrefPage(parent)
{
    QGroupBox *windowAppearanceGroup = new QGroupBox(tr("Window"));
    QPushButton *colorButton = new QPushButton(tr("Color"));
    connect(colorButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));


    QGroupBox *fontGroup = new QGroupBox(tr("Font"));

    fontLabel = new QLabel();
    QPushButton *chooseFontButton = new QPushButton(tr("choose Font"));
    connect(chooseFontButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));


    QVBoxLayout *windowAppearanceLayout = new QVBoxLayout;
    windowAppearanceLayout->addWidget(colorButton);
    windowAppearanceGroup->setLayout(windowAppearanceLayout);

    QVBoxLayout *fontLayout = new QVBoxLayout;
    fontLayout->addWidget(fontLabel);
    fontLayout->addWidget(chooseFontButton);
    fontGroup->setLayout(fontLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(windowAppearanceGroup);
    mainLayout->addWidget(fontGroup);
    mainLayout->addSpacing(12);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    this->load();
}