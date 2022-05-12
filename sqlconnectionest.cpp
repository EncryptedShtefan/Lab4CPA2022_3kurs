#include "sqlconnectionest.h"
#include "QObject"
#include <QMessageBox>

SqlConnectionEst::SqlConnectionEst(QObject* parent) : QSqlQueryModel(parent)
{
    db = QSqlDatabase::addDatabase("QPSQL", "Lab4Connection"); //establishing DB connection
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("1111");
    db.setDatabaseName("Games"); //connection settings

     _isConnectionOpen = true;

    if(!db.open()) //check if connection is successfully opened
    {
        qDebug() << db.lastError().text();
        _isConnectionOpen = false;
    }

    QString m_schema = QString( "CREATE TABLE IF NOT EXISTS games (Id SERIAL PRIMARY KEY, "      //string for sql statement (creating table)
                                "Name text, "
                                "Platform text, "
                                "Creator text, "
                                "Genre text); " );


    QSqlQuery qry(m_schema, db); //thing to manipulate (exec) sql statements

    if( !qry.exec() ) //executing sql script stated above
    {
        qDebug() << db.lastError().text(); //if it wasnt successfully executed
    }

    refresh();
}


QSqlQueryModel* SqlConnectionEst::getModel(){ //getting data model
    return this;
}


bool SqlConnectionEst::isConnectionOpen(){ //returning connection state
    return _isConnectionOpen;
}


QHash<int, QByteArray> SqlConnectionEst::roleNames() const //roles of table fields needed from model for view
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "NameOfGame";
    roles[Qt::UserRole + 2] = "PlatformOfGame";
    roles[Qt::UserRole + 3] = "CreatorOfGame";
    roles[Qt::UserRole + 4] = "GenreOfGame";
    roles[Qt::UserRole + 5] = "ID";

    return roles;
}


QVariant SqlConnectionEst::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    if(role < Qt::UserRole-1)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}


const char* SqlConnectionEst::SQL_SELECT =
        "SELECT Name, Platform, Creator, Genre, Id FROM games";


void SqlConnectionEst::refresh() //updating model after select
{
    this->setQuery(SqlConnectionEst::SQL_SELECT,db);
}


void SqlConnectionEst::add(const QString& nameGame, const QString& platformGame, const QString& creatorGame, const QString& genreGame) //adding data by sql script  (executing INSERT)
{
    QSqlQuery query(db);

    QString strQuery= QString("INSERT INTO games (Name, Platform, Creator, Genre) VALUES ('%1', '%2', '%3', '%4')")
            .arg(nameGame)
            .arg(platformGame)
            .arg(creatorGame)
            .arg(genreGame);

    query.exec(strQuery);

    refresh(); //updating model after inserting
}


void SqlConnectionEst::edit(const QString& nameGame, const QString& platformGame, const QString& creatorGame, const QString& genreGame, const int index) //editing data in table (executing sql UPDATE)
{
    QSqlQuery query(db);

    QString strQuery= QString("UPDATE games SET Name = '%1', Platform = '%2', Creator = '%3', Genre = '%4' WHERE Id = %5")
            .arg(nameGame)
            .arg(platformGame)
            .arg(creatorGame)
            .arg(genreGame)
            .arg(index);

    query.exec(strQuery);

    refresh(); //update after update :))

}


void SqlConnectionEst::del(const int index) //no comments haha classic
{
    QSqlQuery query(db);

    QString strQuery= QString("DELETE FROM games WHERE Id = %1")
            .arg(index);

    query.exec(strQuery);

    refresh();
}


QString SqlConnectionEst::count(const QString& selectedPlatform)
{
    QSqlQuery query(db);

    QString strQuery= QString("SELECT COUNT(ID) FROM games WHERE Platform = '%1'").arg(selectedPlatform);

    query.exec(strQuery);

    QString info;
    while (query.next())
    {
        info = query.value(0).toString();
        qDebug() << info;
    }

    return(info);
}

//sorry I haven't done this lab earlier

