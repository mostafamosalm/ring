
/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
extern "C" {
#include "ring.h"
}
#include "gnetworkaccessmanager.h"

GNetworkAccessManager::GNetworkAccessManager(QObject *parent,VM *pVM)  : QNetworkAccessManager(parent)
{
	this->pVM = pVM;
	this->pParaList = ring_list_new(0);
	strcpy(this->cfinishedEvent,"");

	QObject::connect(this, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedSlot(QNetworkReply*)));

}

GNetworkAccessManager::~GNetworkAccessManager()
{
	ring_list_delete(this->pParaList);
}

 
void GNetworkAccessManager::setfinishedEvent(const char *cStr)
{
	if (strlen(cStr)<100)
		strcpy(this->cfinishedEvent,cStr);
}


void GNetworkAccessManager::finishedSlot(QNetworkReply*)
{
	if (strcmp(this->cfinishedEvent,"")==0)
		return ;
	ring_vm_runcode(this->pVM,this->cfinishedEvent);
}

