#include "qformdoc.h"
#include "ui_qformdoc.h"

QFormDoc::QFormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormDoc)
{
    ui->setupUi(this);
}

QFormDoc::~QFormDoc()
{
    delete ui;
}
