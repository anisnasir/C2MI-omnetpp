#include <string.h>
#include <omnetpp.h>
#include "beacon_m.h"
#include "RREQ_m.h"
#include "RREP_m.h"
#include "DATA_m.h"
#include "ACK_m.h"

struct RoutingEntry{
	char* DestinationName;
	int Port;
	int cost;
};

struct RequestEntry{
	char* DesName;
	int FromHop;
	bool mark;
	int repCost;
};

class Txc1 : public cSimpleModule
{
private:
	int ntCount;
	RoutingEntry neighborTable[20];
	int btCount;
	RoutingEntry backupTable[20];
	int rtCount;
	RoutingEntry routingTable[20];
	int reCount;
	RequestEntry requestTable[20];
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Txc1);

void Txc1::initialize()
{
	ntCount = 0;
	btCount = 0;
	rtCount = 0;
	reCount = 0;

    int count = gateSize("gate");
    for (int i=0;i<count;i++)
    {
        beacon *msg = new beacon();
        msg->setSourceName(getName());
        send(msg, "gate$o",i);
    }

    if (strcmp("S", getName()) == 0)
    {
    	for (int i=0;i<count; i++)
    	{
    		RREQ *rreq = new RREQ();
    		rreq->setDesName("X");
    		rreq->setSrcName("S");
    		rreq->setTimestamp(1);
    		rreq->setCost(0);
    		sendDelayed(rreq,1,"gate$o",i);
    	}
    }
}

void Txc1::handleMessage(cMessage *msg)
{
	if(strcmp(msg->getClassName(),"beacon") == 0)
	{
		beacon *cmsg = check_and_cast<beacon*>(msg);
		const char *dst = cmsg->getSourceName();

		bool entryFoundinNT = false;
		for (int i=0; i<ntCount; i++)
		{
			if (strcmp(neighborTable[i].DestinationName,dst) == 0)
			{
				entryFoundinNT = true;
				break;
			}
		}

		if (!entryFoundinNT)
		{
			//update Neighbor Table
			neighborTable[ntCount].DestinationName = (char*) cmsg->getSourceName();

			bubble(neighborTable[ntCount].DestinationName);
			int baseId = gate("gate$i",0)->getId();
			int arrivedGate = msg->getArrivalGateId() - baseId;

			neighborTable[ntCount].Port = arrivedGate;
			neighborTable[ntCount].cost = 1;//uniform(5.10);
			ntCount++;

			//Send Beacon to arrived port
			beacon *bmsg = new beacon();
			bmsg->setSourceName(getName());
			send(bmsg,"gate$o",arrivedGate);

			//send RREQ to arrived port for all the destinations available in RT
			for(int i=0;i<rtCount;i++)
			{
				RREQ *tmsg = new RREQ();
				tmsg->setSrcName(getName());
				tmsg->setDesName(routingTable[i].DestinationName);
				tmsg->setTimestamp(1);
				tmsg->setCost(0);
				send(tmsg,"gate$o",arrivedGate);
			}
		}
	}
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	else if (strcmp(msg->getClassName(),"RREQ") == 0)
	{
		RREQ *cmsg = check_and_cast<RREQ*>(msg);
		const char *dst = cmsg->getDesName();
		const char *src = cmsg->getSrcName();
//		int  ts = cmsg->getTimestamp();

		//If Source Get the RREQ packet packet should be destroyed
		if(strcmp(src,getName()) == 0)
		{
			bubble("I have already requested for it");
			return;
		}

		int baseId = gate("gate$i",0)->getId();
		int arrivedPort = msg->getArrivalGateId() - baseId;

		int costArrivedPort = 0;
		for (int i=0;i<ntCount;i++)
		{
			if(neighborTable[i].Port == arrivedPort)
				costArrivedPort = neighborTable[i].cost;
		}

		//Add Source in Backup Table
		bool exist = false;
		for(int i =0;i<btCount;i++)
		{
			if((strcmp(backupTable[i].DestinationName,cmsg->getSrcName()) == 0) && backupTable[i].Port == arrivedPort)
				if(backupTable[i].cost > (cmsg->getCost()+costArrivedPort))
					{
						backupTable[i].cost = cmsg->getCost()+costArrivedPort;
						exist = true;
					}
		}
		if(!exist)
		{
			backupTable[btCount].DestinationName = (char*)cmsg->getSrcName();
			backupTable[btCount].cost = cmsg->getCost()+costArrivedPort;
			backupTable[btCount].Port = arrivedPort;
			btCount++;
		}
		cmsg->setCost(cmsg->getCost()+costArrivedPort);

		int entryAt = -1;
		bool entryFoundinRT = false;

		//Check whether source exist in Routing Table
		for (int i=0; i<rtCount; i++)
		{
			if (strcmp(routingTable[i].DestinationName,src) == 0)
			{
				entryFoundinRT = true;
				entryAt = i;
				break;
			}
		}

		//if Source is present in RT with greater cost replace cost
		if(entryFoundinRT)
		{
			if(routingTable[entryAt].cost > cmsg->getCost())
				routingTable[entryAt].cost = cmsg->getCost();
		}else // if Source is not present in RT add Source
		{
			routingTable[rtCount].DestinationName = (char*)src;
			routingTable[rtCount].cost = cmsg->getCost();
			routingTable[rtCount].Port = arrivedPort;
			rtCount++;
		}

		//If Current node is destination or RT contains Destination send RREP

		entryFoundinRT = false;
		for (int i=0; i<rtCount; i++)
		{
			if (strcmp(routingTable[i].DestinationName,dst) == 0)
			{
				entryFoundinRT = true;
				entryAt = i;
				break;
			}
		}
		if((strcmp(getName(),dst) == 0) || 	entryFoundinRT)
		{
			RREP *tmsg = new RREP();
			tmsg->setDesName(dst);
			tmsg->setCost(0);
			if(entryFoundinRT)
				tmsg->setCost(routingTable[entryAt].cost);
			//tmsg->setTimestamp(1);
			send(tmsg,"gate$o",arrivedPort);
		}else
		{
			entryFoundinRT = false;
			entryAt = -1;
			for(int i=0;i<reCount;i++)
				if(strcmp(requestTable[i].DesName,dst) == 0)
					{
						entryFoundinRT = true;
						entryAt = i;
					}

			if(!entryFoundinRT)
			{
				for(int i=0;i<ntCount;i++)
				{
					if(neighborTable[i].Port != arrivedPort)
					{
						RREQ *tmsg = new RREQ();
						tmsg->setDesName(cmsg->getDesName());
						tmsg->setSrcName(cmsg->getSrcName());
						tmsg->setCost(cmsg->getCost());
						send(tmsg,"gate$o",neighborTable[i].Port);
					}

				}
				requestTable[reCount].FromHop = arrivedPort;
				requestTable[reCount].DesName = (char *) dst;
				requestTable[reCount].mark = false;
				requestTable[reCount].repCost = 999;
				reCount++;
			}
			else
			{
				if(requestTable[entryAt].mark)
				{
					return;
				}
				else
				{
					send(cmsg,"gate$o",arrivedPort);
					requestTable[entryAt].mark = true;
				}
			}
		}

	}

	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	else if (strcmp(msg->getClassName(),"RREP") == 0)
	{
		RREP *cmsg = check_and_cast<RREP*>(msg);

		const char* dst = cmsg->getDesName();
		int cost = cmsg->getCost();

		int baseId = gate("gate$i",0)->getId();
		int arrivedPort = msg->getArrivalGateId() - baseId;


		int costArrivedPort = 0;
		for (int i=0;i<ntCount;i++)
		{
			if(neighborTable[i].Port == arrivedPort)
				costArrivedPort = neighborTable[i].cost;
		}
		int totalCost = cost + costArrivedPort;

		//Add destination in BT
		backupTable[btCount].DestinationName = (char *) dst;
		backupTable[btCount].Port = arrivedPort;
		backupTable[btCount].cost = totalCost;
		btCount++;

		int entryAt = -1;
		bool entryFoundinRT = false;

		//Check whether destination exist in Routing Table and cost is less
		for (int i=0; i<rtCount; i++)
		{
			if (strcmp(routingTable[i].DestinationName,dst) == 0 && routingTable[i].cost > totalCost)
			{
				entryFoundinRT = true;
				entryAt = i;
				routingTable[i].cost = totalCost;
				routingTable[i].DestinationName = (char *) dst;
				routingTable[i].Port = arrivedPort;
				break;
			}
		}

		//if destination not present in RT
		if( !entryFoundinRT)
		{
			routingTable[rtCount].cost = totalCost;
			routingTable[rtCount].DestinationName = (char *) dst;
			routingTable[rtCount].Port = arrivedPort;
			rtCount++;
		}

		//send rrep to all nodes that requested for destination
		if(strcmp(getName(),"S") == 0)
		{
			bubble("lalalalala");
			DATA *data = new DATA();
			data->setDesName("X");
			data->setSrcName("S");
			data->setPayload("hello");
			for(int i =0; i<rtCount;i++)
				if(strcmp(routingTable[i].DestinationName,"X") == 0)
				{
					send(data,"gate$o",routingTable[i].Port);
					break;
				}
			return;
		}

		for (int i=0; i<reCount; i++)
		{
			if((strcmp(requestTable[i].DesName,dst) == 0) && requestTable[i].repCost > totalCost)
			{
				RREP *tmsg = new RREP();
				tmsg->setDesName(dst);
				tmsg->setCost(totalCost);
				requestTable[i].repCost = totalCost;
				send(tmsg,"gate$o",requestTable[i].FromHop);
			}
		}
	}
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	else if(strcmp(msg->getClassName(),"DATA") == 0)
	{
		int baseId = gate("gate$i",0)->getId();
		int arrivedPort = msg->getArrivalGateId() - baseId;

		if(strcmp(getName(),"X") == 0)
		{
			ACK *amsg =  new ACK();
			amsg->setSrcName("X");
			amsg->setDesName("S");
			send(amsg,"gate$o",arrivedPort);
			bubble("got the packet");
			return;
		}
		DATA *data = check_and_cast<DATA*>(msg);
		const char *dst = data->getDesName();

		for(int i =0; i<rtCount;i++)
			if(strcmp(routingTable[i].DestinationName,dst) == 0)
			{
				send(data,"gate$o",routingTable[i].Port);
				break;
			}

	}
	else
	{
		ACK *ack = check_and_cast<ACK*>(msg);
		const char * des = ack->getDesName();
		const char* src = ack->getSrcName();
		if(strcmp(getName(),"S") == 0)
		{
			bubble("Got acknowledge");
			DATA *data = new DATA();
			data->setDesName("X");
			data->setSrcName("S");
			data->setPayload("hello");
			for(int i =0; i<rtCount;i++)
			if(strcmp(routingTable[i].DestinationName,"X") == 0)
			{
				send(data,"gate$o",routingTable[i].Port);
				break;
			}
			return;
		}

		for(int i =0; i<rtCount;i++)
			if(strcmp(routingTable[i].DestinationName,des) == 0)
			{
				ACK *amsg =  new ACK();
				amsg->setSrcName(src);
				amsg->setDesName(des);

				send(amsg,"gate$o",routingTable[i].Port);
				break;
			}

	}
}

