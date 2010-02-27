/*
 * DataMaintenanceDB.cpp
 *
 * Copyright (C) 2006-2007 Rilson Nascimento
 *
 * 17 July 2006
 */

#include <transactions.h>

using namespace TPCE;

// Call Data Maintenance Frame 1
void CDataMaintenanceDB::DoDataMaintenanceFrame1(
		const TDataMaintenanceFrame1Input *pIn,
		TDataMaintenanceFrame1Output *pOut)
{
	ostringstream osCall;
	osCall << "SELECT * FROM DataMaintenanceFrame1(" <<
			pIn->acct_id << ", " <<
			pIn->c_id << ", " <<
			pIn->co_id << ", " <<
			pIn->day_of_month << ", '" <<
			pIn->symbol << "', '" <<
			pIn->table_name << "', '" <<
			pIn->tx_id << "', " <<
			pIn->vol_incr << ")";
#ifdef DEBUG
	m_coutLock.lock();
	cout << "<<< DMF1" << endl;
	cout << "*** " << osCall.str() << endl;
	cout << "- Data Maintenance Frame 1 (input)" << endl <<
			"-- c_id: " << pIn->c_id << endl <<
			"-- co_id: " << pIn->co_id << endl <<
			"-- day_of_month: " << pIn->day_of_month << endl <<
			"-- symbol: " << pIn->symbol << endl <<
			"-- table_name: " << pIn->table_name << endl <<
			"-- tx_id name: " << pIn->tx_id << endl <<
			"-- vol_incr: " << pIn->vol_incr << endl;
	m_coutLock.unlock();
#endif // DEBUG

	BeginTxn();
	// Isolation level required by Clause 7.4.1.3
	m_Txn->exec("SET TRANSACTION ISOLATION LEVEL READ COMMITTED;");
	result R( m_Txn->exec( osCall.str() ) );
	CommitTxn();

	result::const_iterator c = R.begin();
 	pOut->status = c[0].as(int());

#ifdef DEBUG
	m_coutLock.lock();
	cout << "- Data Maintenance Frame 1 (output)" << endl <<
			"-- status: " << pOut->status << endl;
	cout << ">>> DMF1" << endl;
	m_coutLock.unlock();
#endif // DEBUG
}
