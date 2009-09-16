#include "ClientApplication.h"

#include "HorusStyle.h"

int main(int argc, char *argv[])
{
    ClientApplication app(argc, argv);
	app.setStyle(new HorusStyle());
    return (app.exec());
}
