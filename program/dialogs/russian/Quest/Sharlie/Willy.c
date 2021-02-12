// Вильям Патерсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ты что-то хотел?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Здравствуйте, месье. Черт возьми, так это вы развернули тут военные действия?!";
			link.l1 = TimeGreeting()+", сударь. Да, это с моего корабля был высажен десант. А в чем, собственно говоря, дело? Кто вы такой? Как я полагаю - англичанин?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "Шотландец, месье. Капитан английского флота Вильям Патерсон. А это мой первый помощник и правая рука - Арчибальд Колхаун. Дело в том, что там, в джунглях, находится укрепленная база испанцев, и моя задача - выбить проклятых негодяев из форта, который они нахально отстроили в непосредственной близости от английских владений и угнездились в нем\nСовсем недавно нами была предпринята попытка штурма, однако мерзавцы, несмотря на понесенные потери, сумели выстоять. Я отправился за подкреплением и...";
			link.l1 = "Подкрепление вам не понадобится. Я довершил начатое вами дело - форт в джунглях пуст. Командир испанцев, Диего де Монтойя, мертв, а его эскадра, прибывшая сюда, видимо, на подмогу - уничтожена.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "Что за самоуправство? На каком основании вы развязали боевые действия на английской территории?";
			link.l1 = "Смею напомнить, капитан Патерсон, что здесь не Белиз. Какие английские владения? А весь сыр-бор разгорелся из-за дона Диего де Монтойя, который имел такую неосторожность атаковать меня и мои корабли.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "Кхм... и с чего бы это дону Диего было нападать на вас, а, капитан?";
			link.l1 = "У нас с ним давняя вражда... Еще с того дня, когда эскадра, возглавляемая им, напала на колонию Сен-Пьер и чуть позже была уничтожена при моем непосредственном участии.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "Черт побери! Мне нужен был этот досточтимый кабальеро в живом виде! Я собирался допросить его, зачем он устроил в джунглях военную базу. Это ведь неспроста...";
			link.l1 = "Сожалею, но он теперь вам уже ничего не скажет. Впрочем, в форте могут быть раненые солдаты гарнизона - быть может, они разговорятся?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Солдаты... да что толку от тупоголовых солдафонов!.. Где труп дона Диего? При нем могли быть важные документы!";
			link.l1 = "Я оставил дона Диего на полу оружейной форта. Если он вам так нужен - вы сможете найти его там. Не думаю, что он куда-то сбежал.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Эх, и вот кто вас просил лезть не в свое дело... принесла вас нелегкая на мою голову...";
			link.l1 = "Капитан, я не понимаю ваших упреков. Я сделал вашу работу, положил своих людей в бою, сам рисковал жизнью - а вы недовольны. Вам остается только доложить в Порт-Рояль об успехе миссии и всех дел. Я не буду претендовать на вашу славу, заверяю.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "Претендовать? Да какая тут слава?! Вы ничего не понимаете.. эх, ладно. Прощайте, сударь.";
			link.l1 = "И вам всего доброго!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("VOICE\Russian\sharlie\Willie Paterson.wav");
			dialog.text = "И правду говорят, что у вас, как у кошки - девять жизней! "+TimeGreeting()+", месье де Мор. Что-то вы неважно выглядите...";
			link.l1 = TimeGreeting()+", мистер Патерсон. Надо сказать, вы все очень ловко разыграли с вашим другом Арчибальдом, черт бы вас побрал! Я даже и не догадался...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Но-но, не стоит чертыхаться на пороге вступления в Царствие Небесное. Не догадались? Я польщен: мне удалось обвести вокруг пальца одного из известнейших интриганов архипелага. Согласитесь, идея с дневником была гениальной, да?\nМне нужно было затащить вас в место, о котором никто не знает - уж больно рискованно было открыто ликвидировать вас - чревато крупным скандалом, ведь вы же друг шевалье Филиппа де Пуанси, так?.. А теперь вы исчезнете бесследно, и никто не узнает - как.";
			link.l1 = "Получается, все, что рассказал мне Колхаун - ложь?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "Отнюдь. Я действительно нашел беднягу Арчибальда на этом самом острове. Вот только мемуаров никаких он не сочинял - дневник, который вы нашли в комнате Арчи в Порт-Рояле, куда пробрались столь изысканным способом, был написан им под мою диктовку, специально для вас, месье де Мор\nЯ давно за вами наблюдаю, с самого того дня, как мы встретились на мысе Каточе. Ведь это вы забрали с трупа дона Диего карту Двух Появлений? Не отпирайтесь: я знаю, что это вы.";
			link.l1 = "Вам тоже известно о Страже Истины?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "Глупый вопрос. Конечно, известно. Мне также известно и то, что дага 'Коготь вождя' также находится у вас. И вы скоро отдадите эти предметы, которые вам не принадлежат.";
			link.l1 = "Я рад, что вы не виляете, как дон Диего. Люблю честность и прямоту. Как я понимаю, компас 'Стрела пути' у вас?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "Хо-хо! Ну, будем честны до конца... неужели вы думаете, сударь, что я такой же идиот, как вы и дон Диего, что таскаю столь ценные предметы с собой? Компас лежит на Ямайке, и даже не в Порт-Рояле, а в месте, где никому даже в голову не придет его искать, и под надежным замком. Но вам эта информация не пригодится.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "Как я понимаю, вы меня уже похоронили, мистер Патерсон? Смею заметить, у кошки осталась в запасе еще одна жизнь!.. Где мои офицеры?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "Как я понимаю, вы меня уже похоронили, мистер Патерсон? Смею заметить, у кошки осталась в запасе еще одна жизнь!..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "Переживаете за свою подружку, капитан? Ваша девка лежит вон там, в кустах, с дыркой во лбу. Она проложила вам дорожку, и вы скоро отправитесь следом за ней.";
				link.l1 = "Ты за это дорого заплатишь, ублюдок!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "Ваши офицеры проложили вам дорогу, месье де Мор. Они лежат вон там, в кустах. Скоро и вы отправитесь следом.";
				link.l1 = "Это мы еще посмотрим!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "Мы позаботимся о том, чтобы она стала действительно последней.";
			link.l1 = "Это мы еще посмотрим!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "Вы смешны. В одиночку против целого отряда! Впрочем, довольно увлекательных бесед... Мушкеты на изготовку! Пли!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}