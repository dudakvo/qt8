#include <QCoreApplication>
#include <iostream>
#include <boost/program_options.hpp>
#include "QString"
#include "QByteArray"

#include "QFile"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string filePath;
    QFile file;
    QString qStringFilePath;
    QByteArray fData;

    boost::program_options::options_description optionDescription("Allowedoptions");
    optionDescription.add_options()
        ("help", "Produce help message")
        ("path", boost::program_options::value<std::string>(), "--path <file path>")
        ;
    boost::program_options::variables_map vm;
    try {

    boost::program_options::store(boost::program_options::parse_command_line(argc,
                                                                             argv,
                                                                             optionDescription),
                                  vm);
    boost::program_options::notify(vm);

    if (vm.count("help"))
    {
        std::cout << optionDescription << std::endl;
    }
    if (vm.count("path"))
    {
        filePath = vm["path"].as<std::string>();
        qStringFilePath.append(filePath.c_str());
    }

    }
    catch(std::exception)
    {
         std::cout << optionDescription << std::endl;
         std::cout <<"file --path <file path>";
         exit(1);
    }

    if(!QFile::exists(qStringFilePath))
    {
        //qCritical("File %s does not exists.", qPrintable(qStringFilePath));
        qCritical("ERROR: File %s does not exists.", qPrintable(qStringFilePath));
        return 1;
    }

    file.setFileName(qStringFilePath);

    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
    qCritical("Error %d : %s.", file.error(),
    qPrintable(file.errorString()));
    return 2;
    }

    fData=file.readAll();

    std::cout<< QString(fData).toStdString();

    file.close();

    return a.exec();
}
