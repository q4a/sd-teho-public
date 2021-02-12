object Tornado;

void WhrDeleteTornadoEnvironment()
{
	if (isEntity(&Tornado)) 
	{ 
		DeleteClass(&Tornado);
		DeleteAttribute(&Tornado,"");
	}
}

void WhrCreateTornadoEnvironment()
{
	aref aCurWeather = GetCurrentWeather();
	
	DeleteAttribute(&Tornado,"");

	if (sti(aCurWeather.Tornado) != true) return;

	if (!isEntity(&Tornado)) 
	{ 
		CreateEntity(&Tornado,"Tornado");
	}
	
	Tornado.x = 10000.0;
	Tornado.z = 10000.0;

	SendMessage(&Tornado, "lf", 0, 300.0 + frnd() * 600.0);
	LayerAddObject(SEA_EXECUTE, &Tornado, 65535);
	LayerAddObject(SEA_REALIZE, &Tornado, 65535);
}

void WhrCreateTornadoEnvironmentEx()
{
	aref aCurWeather = GetCurrentWeather();
	
	DeleteAttribute(&Tornado,"");

	if (!isEntity(&Tornado)) 
	{ 
		CreateEntity(&Tornado,"Tornado");
	}
	
	Tornado.x = 0.0;
	Tornado.z = 0.0;

	SendMessage(&Tornado, "lf", 1, 0.3); // 0.5 -> скорость вращения замедлена в 2 раза

	if( bSeaActive && !bAbordageStarted)
	{
		LayerAddObject(SEA_EXECUTE, &Tornado, 65535);
		LayerAddObject(SEA_REALIZE, &Tornado, 65535);
	}
	else
	{
		LayerAddObject("execute", &Tornado, 65535);
		LayerAddObject("realize", &Tornado, 65535);
	}
}
