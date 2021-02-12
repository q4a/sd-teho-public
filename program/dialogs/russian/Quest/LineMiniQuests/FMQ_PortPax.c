// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("VOICE\Russian\z_arest_02.wav");
			dialog.text = "Что здесь происходит, господа?! Драка?!";
			link.l1 = "Уф... Офицер, я пришёл на крики о помощи подавальщицы таверны, и увидел, что...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Капитан "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "Вы, капитан, пока можете быть свободны. Картина происшествия мне ясна. Если вы понадобитесь - мы вас вызовем.";
			link.l1 = "Хорошо...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("VOICE\Russian\z_arest_02.wav");
			dialog.text = "Что здесь происходит?! Драка?!";
			link.l1 = "Уф... Офицер, я пришёл сюда на крики о помощи подавальщицы таверны, и увидел, что на благородного дворянина напали два негодяя. Я попытался спасти беднягу, но, увы - не смог. Мерзавцы расправились с ним.";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Так-так... Да этот дворянин - испанец! И что ему тут надо было? Гм. Ваше имя, месье?";
			link.l1 = ""+GetFullName(pchar)+". Капитан "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Капитан, пока можете быть свободны. Подавальщица всё так и описала... картина происшествия мне ясна. Если вы понадобитесь - мы вас вызовем.";
			link.l1 = "Хорошо...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			PlaySound("VOICE\Russian\YoungMan03.wav");
			dialog.text = "Позвольте мне всё объяснить, офицер! Я, дон Доминго Ортис Альбалате из Санто-Доминго, прибыл в Порт-о-Пренс по приглашению одной юной особы. В ожидании встречи я остановился в таверне. Однако не прошло и двух часов, как ко мне в комнату вломились dos canallas malditas, и если бы не помощь этого доброго сеньора, появившегося как раз вовремя, мне пришлось бы туго.";
			link.l1 = "Дон Доминго Ортис Альбалате? Испанец?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "Именно так, сеньор! Прошу вас учесть, что я нахожусь во французской колонии на законных основаниях и что я испанский дворянин благородного происхождения, а не какой-то там pirata sucia!";
			link.l1 = "Дон Доминго, вам следует пройти со мной в комендатуру для выяснения! Мы во всём разберемся. А вы, месье...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("VOICE\Russian\YoungMan01.wav");
			dialog.text = "Сеньор капитан! Сеньор капитан! Клянусь честью моего доброго отца, вы благородный человек! Я бы хотел с вами увидеться, позже, и отблагодарить, как положено. Окажите честь посетить моё скромное жилище в Санто-Доминго! Мой дом находится совсем рядом с городскими воротами. Буду ждать вас, caballero valeroso! Запомните моё имя - дон Доминго Ортис Альбалате!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			PlaySound("VOICE\Russian\YoungMan03.wav");
			dialog.text = "Капитан "+GetFullName(pchar)+"?! О! Какой ужас! Да тут настоящая скотобойня! Что здесь произошло, mi buen amigo? Кто эти люди? ";
			link.l1 = "Рад вас видеть, дон Доминго! Эти люди... Я пришёл по вашему приглашению, на пороге меня встретил некий господин, который во-он там лежит, видите? Он сказал, что его зовут Уго, он ваш слуга и...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Уго?! О, нет, вас подло обманули, капитан!";
			link.l1 = "Я понял это слишком поздно! Три мерзавца проникли в ваш дом, убили вашего верного слугу Уго - его труп я нашёл наверху уже потом - и устроили засаду. Караулили, вне сомнения, вас, сеньор Альбалате. Моё появление спутало им планы - я захотел остаться, ну... они и начали махать клинками. Но не на того напали!";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Oh, Dios! Вы работаете шпагой, как профессиональный кондотьер! Хорошо, что вы на моей стороне! О, мой бедный Уго! Он нянчил меня с детства, а теперь... убит безродными псами!";
			link.l1 = "Дон Доминго, осмелюсь предположить, что кто-то сильно жаждет вашей смерти! Ваш добрый слуга знал об опасности, грозящей вам. Я нашёл на столе записку. Прочтите.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Покажите... (читает) Неужели... о, нет! Я просто не верю в это! Дядя Луис... Но...";
			link.l1 = "У вас появились догадки?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Пока только предположения... Ужасные предположения, сеньор! Неужели брат моей матушки, дядя Луис, мог пойти на такое?";
			link.l1 = "Какой кошмар! Ваш дядя? Может, расскажете поподробнее? ";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Вы правы, mi buen amigo! Я расскажу вам всё - ведь вы сегодня во второй раз спасли меня и... похоже, что вы единственный, кому я теперь могу доверять! Но давайте же уйдём отсюда - нынешняя обстановка моего дома вызывает у меня приступы тошноты. Я сообщу алькальду, и здесь приберутся, а бедного Уго подготовят к погребению. А мы с вами пройдём в таверну, и побеседуем за кружкой лучшего вина!";
			link.l1 = "Согласен, сеньор! Идемте!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			PlaySound("VOICE\Russian\YoungMan02.wav");
			dialog.text = "Итак, друг мой, позвольте мне кратко рассказать историю моей семьи. Моя матушка, донна Изабелла Ортис, вышла замуж за моего батюшку, маркиза Рикардо Альбалате, и приняла его фамилию, как водится. Брат моей матушки, Луис Ортис, занимал в колониях должность то ли командующего гарнизоном, то ли вовсе тюремного смотрителя, но после замужества своей сестры получил от моего отца должность управляющего плантацией близ Порто-Белло\nЭто большая и очень богатая плантация, приносящая солидный доход. После трагической гибели моей милой матушки и моего отца в море, я унаследовал все права на имущество моего родителя. Дядя остался управляющим, а меня устраивала рента, которую он мне регулярно и в срок выплачивал.";
			link.l1 = "Но кому же тогда вы помешали?";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Мой дядюшка всего лишь управляющий, а хозяин - я. Если меня вдруг не станет, то плантация перейдёт в его руки целиком и полностью.";
			link.l1 = "Так вот в чём дело! Ох уж эти родственнички! А вы знаете, сеньор, вот мой дорогой братец... впрочем, я расскажу об этом потом. Продолжайте.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "Мой верный Уго в своей предсмертной записке упомянул про бумаги дяди... Это прямое указание. О, как я не хочу верить в это! Но... моя кузина, Маргарита Ортис, проживающая в Испании, недавно была помолвлена с инфантом весьма видного дворянского семейства. Не в этом ли дело, дорогой капитан, как вы считаете?";
			link.l1 = "Конечно! Вашему дядюшке срочно понадобились деньги на свадьбу, и он решил вас устранить!";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Деньги?! О! Да, безусловно, но... и титул маркиза! Конечно! А моя кузина станет таким образом достойной парой своему будущему мужу! О, Небеса! Как же я был глуп!";
			link.l1 = "Какое коварство со стороны брата матери! Впрочем, дон Доминго, а вы знаете, что мой собственный отец...";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Постойте, мой друг! Это ведь не первая попытка! С пару недель назад, как раз вскоре после объявления о помолвке, был один пьяный паршивец, имевший наглость обхамить меня так, что пришлось преподать ему урок хороших манер. Когда дошло до клинков, этот мужлан оказался не последним фехтовальщиком! Он даже умудрился задеть меня шпагой... перед собственной смертью...";
			link.l1 = "Ха! Поделом досталось наглецу! А как вы оказались в таверне Порт-о-Пренса? Вы что-то говорили о юной особе?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(краснеет) О, да... Да, капитан, была там и милая особа... но только теперь я понимаю, что это была ловушка, а юная прелестница - морская сирена! О, кругом столько мерзавцев, столько мерзавцев, друг мой, я никому не могу верить! Верный Уго... и тот мёртв!";
			link.l1 = "Как я вас понимаю! Знали бы вы, сеньор, сколько у меня во Франции было... неприятностей из-за милых и юных девиц! Но вам надо что-то предпринять, дон Доминго. Может, тайком отплыть в Испанию и навестить вашу кузину?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "В Испанию! И отдать мою плантацию дядюшке? Нет, капитан, не бывать тому, и это так же верно, что меня зовут маркиз Доминго Ортис Альбалате!";
			link.l1 = "Но...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = "Друг мой, могу я просить вас о помощи? После кончины несчастного Уго, у меня нет более близких людей, а вы - дважды, дважды отводили от меня вражеский клинок! Я обязан вам больше, чем кому-то другому! Я ваш должник, и я смею просить вас ещё об одной услуге, но клянусь моим титулом, я достойно отблагодарю вас!";
			link.l1 = "Чем же я могу помочь вам, сеньор?";
			link.l1.go = "noble_20";
		break;
		
		case "noble_20":
			dialog.text = "Отправимся в Порто-Белло, на мою плантацию! Я знаю, что мой дядюшка сейчас в Картахене. Уго упомянул о каких-то документах... вот мы и поищем хорошенько в деловых книгах и фолиантах дона Луиса Ортиса! Глядишь - на свет Божий явится нечто, что откроет мне истинную личину моего дядюшки. До Порто-Белло путь неблизкий, но я хорошо заплачу вам за переход!";
			link.l1 = "Я был бы последним мерзавцем, если бы отказал вам, дон Доминго! Мой долг - быть на вашей стороне в этой гнусной истории!";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Я знал, что вы мне поможете, кабальеро! Вот, возьмите - здесь двадцать тысяч песо. Это компенсация ваших расходов на переход к Порто-Белло. Когда мы отправляемся? Надо спешить, пока дядюшка не вернулся из Картахены!";
			link.l1 = "Медлить не будем.";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20) link.l1.go = "noble_22";
			else link.l1.go = "noble_22x";
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Чтобы у нас не возникло проблем, мы оформим на вас лицензию Голландской Вест-Индской	торговой Компании. У меня есть заполненный бланк на 20 дней, впишем только ваше имя.";
			link.l1 = "Это просто замечательно!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Вы позволите мне подняться на борт вашего судна немедленно, друг мой?";
			link.l1 = "Конечно. А как только поднимется ветер посвежее - сразу ставим паруса.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
		break;
		
		case "noble_23":
			PlaySound("VOICE\Russian\YoungMan03.wav");
			dialog.text = "Итак, капитан, вот мы и на месте. Теперь надо найти дом моего дядюшки на плантации и хорошенько порыться там...";
			link.l1 = "Я полагаю, вопросов с охраной не возникнет?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "Нет. Хотя, м-м-м... не исключаю, что Луис мог их настроить против меня. В любом случае, осторожность не повредит. Идёмте, будем искать нужный дом.";
			link.l1 = "А вы разве не знаете расположение домов на вашей плантации?";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Кхм... Увы, мой друг, к своему стыду должен признаться, что на этой плантации я последний раз был очень давно, ещё в совсем юном возрасте... но я намерен исправить сие досадное упущение!";
			link.l1 = "Ну и неважно! Мы найдём дом вашего дяди сами.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "Что это у вас, мой друг?";
			link.l1 = "Гляньте, дон Доминго. Тут какие-то цифры, бухгалтерские отчёты. Может, это будет интересно?";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(смотрит) Гм... Да, точно. Так-так... О! Сто тысяч песо! И ещё сто пятьдесят тысяч! А тут... (листает) Ай да дядя Луис!";
			link.l1 = "Обнаружили что-то?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Что-то! Да мой драгоценный дядюшка получал прибыли с плантации в пять раз больше, чем говорил мне! Мошенник!";
			link.l1 = "Каков негодяй, а?! Бесчестно обкрадывать хозяина, пользуясь его отсутствием! Вы не должны были доверять этому проходимцу!";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Вы как всегда правы, капитан! Мой гнусный родич жирует за мои деньги! Это моё упущение... Но я всё исправлю! Я - владелец плантации, а дядюшка с сегодняшнего дня - никто!";
			link.l1 = "Вот это правильно! Выгоните его в три шеи! Он, конечно, будет не согласен с этим...";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "А мне плевать, согласен он или нет! Я маркиз Доминго Ортис Альбалате, а Луис Ортис - всего лишь управляющий! Был им! И он...";
			link.l1 = "Доминго, а что, если ваш дядя окажет сопротивление? Ведь ему так сладко жилось, обкрадывая вас.";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Сопротивление? Вы серьзно? Ха! Солдатня не осмелится поднять руку на испанского гранда, а сам дядя, если решится - пусть бросит мне вызов! Я заколю его на дуэли, как свинью!";
			link.l1 = "А если он предъявит какие-нибудь права на плантацию? Он ведь ваш родственник, и ему могло полагаться что-то от вашего наследства...";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ха! Знаете, что мы сейчас сделаем? Мы пойдём к сеньору Луису де Монтаносу - губернатору Порто-Белло. В этом гроссбухе дядюшка имел неосторожность описать сделки с контрабандистами - он покупал у них рабов по дешёвке. Эта книга сослужит нам добрую службу - я упеку негодяя в тюрьму и оттуда он не сможет мне вредить! Идёмте же скорее, caballero! В Порто-Белло!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			dialog.text = "Это гнусная, наглая ложь! Да как смеет этот мерзавец, которого я считал своим дядей, своим поганым языком порочить память моей матушки и моего отца! Карамба, я вырву его грязный язык за эти слова! Доставай свою шпагу, подлец, подсылающий наёмных убийц!!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("VOICE\Russian\YoungMan01.wav");
			dialog.text = "Дядя Луис отправился туда, где ему самое место - в преисподнюю... Вас послали мне сами Небеса, кабальеро! Я рад, что вы не поверили словам этого негодяя! На какой-то момент я даже испугался - что вы уйдёте и оставите меня в лапах этого мерзавца\nДа, сеньор, я не безупречен, но эта гнусность -  мол, я нанял пиратов для убийства своих родителей!.. О нет, каким же подонком надо быть, чтобы обвинить меня в таком, в таком! Ну ничего, он своё получил!";
			link.l1 = "Рад, что мы вышли целыми из этой передряги, дон Доминго. Что нам делать дальше? Надеюсь, нам не предъявят обвинение?";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "Обвинение?! Ха-ха! Я покажу любому обвинителю дядюшкин гроссбух с контрабандными сделками! И скажу, что во время ревизии негодяй попытался убить владельца плантации, благо, свидетелей того, как он напал на нас со своими клевретами - предостаточно. Не извольте волноваться, mi buen amigo. Мне пора показать наконец, кто здесь хозяин!";
			link.l1 = "Правильно! И обязательно выясните, кто пособничал вашему дяде в воровстве, и примерно накажите мерзавцев!";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "Я так и поступлю, капитан! И если кто задумает чинить мне козни - пощады не будет! А теперь позвольте выразить вам свою глубочайшую признательность и благодарность, кабальеро! Я так рад, "+pchar.name+", что встретил вас на Эспаньоле! Сейчас вам нужно отдохнуть - ступайте в таверну Порто-Белло, выпейте чашу доброго вина, поспите, а завтра приходите сюда, в дом дядюшки\nЯ бы с удовольствием присоединился к вам, но... мне и в самом деле пора входить в курс дел на плантации. Жду вас завтра, капитан, я приготовлю для вас достойную награду!";
			link.l1 = "Хорошо, дон Доминго. До завтра.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			PlaySound("VOICE\Russian\YoungMan02.wav");
			dialog.text = "О, а вот и вы, мой дорогой друг!";
			link.l1 = "Как дела, дон Доминго? Как плантация?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "Дела на плантации идут отлично, но вот все деньги пройдоха-дядюшка переводил в Картахену и хранил в тамошнем банке. Боюсь, чтобы вернуть своё золото, мне придётся изрядно походить по судам и адвокатам. Но ничего, я этим займусь! Однако вы не печальтесь, капитан: я, как и обещал, достойно отплачу за ваше благородство!";
			link.l1 = "Когда я помогал вам в сражениях, я не думал о наградах, сеньор!..";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "Я знаю, "+pchar.name+", и это делает вам честь! Итак, хотя денег у меня на данный момент нет, я загружу ваш корабль товарами моей собственной плантации - мешками с кофе. Вы сможете выгодно продать его.";
			link.l1 = "Ого! Это неплохо...";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Кроме того, у меня есть несколько вещей, которые мне точно не понадобятся, а вам, моряку и капитану, очень пригодятся: это хорошая подзорная труба и три амулета. Возьмите, это всё ваше.";
			link.l1 = "Спасибо!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("Вы получили хорошую подзорную трубу");
			Log_Info("Вы получили три амулета");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ну и, наконец, в знак моей высочайшей признательности к вам и во имя нашей дружбы я дарю вам свою рапиру. Она хорошо служила мне - пусть теперь послужит и вам. И вы, глядя на неё, всегда будете вспоминать своего испанского друга - маркиза Доминго Альбалате!";
			link.l1 = "Благодарствую, сеньор! Не ожидал...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("Вы получили 'Смоллсворд'");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Ну а теперь я, к величайшему сожалению, вынужден с вами проститься. Мне нужно отправляться в Порто-Белло - назначена аудиенция у губернатора, затем отплывать в Картахену... В общем, моя прежняя весёлая жизнь подошла к концу, пора начинать жить по-новому. Мне так жаль с вами расставаться, "+pchar.name+"! Мы могли бы так славно кутить вдвоём! Ром, вино, красивые девицы...";
			link.l1 = "Я вас так понимаю, caballero! У нас с вами много общего! Но увы - нас обоих ждут дела. Скучные, унылые дела. Эх!..";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "Это точно. Был очень рад знакомству, мой друг! Заходите в гости! У нас ещё будет время вдоволь повеселиться! Удачи в море!";
			link.l1 = "И вам успехов в управлении плантацией, дон Доминго!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("VOICE\Russian\YoungMan02.wav");
			dialog.text = "Эх, поздновато мы с вами прибыли, сеньор! Мой дядюшка-пройдоха, похоже, уже подчистил все следы. Видать, ему доложили, что произошло в Санто-Доминго, и он принял меры... Но я этого так не оставлю! Я отправляюсь в Порто-Белло, к губернатору, и инициирую судебный процесс против дяди. Довольно ему распоряжаться моим имуществом.";
			link.l1 = "Правильно! Засудите негодяя! Он заслужил это.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "Ну а вам, капитан, я хочу сказать огромное спасибо! Был очень рад нашему знакомству! И в знак моей признательности я дарю вам свою рапиру. Она хорошо служила мне - пусть теперь послужит и вам. И вы, глядя на неё, всегда будете вспоминать своего испанского друга - маркиза Доминго Альбалате!";
			link.l1 = "Благодарствую, сеньор! Не ожидал...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("Вы получили 'Смоллсворд'");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, "blade_16");
			dialog.text = "Ну а теперь я, к величайшему сожалению, вынужден с вами проститься. Мне нужно отправляться в Порто-Белло. Моя прежняя беззаботная жизнь подошла к концу. Мне так жаль с вами расставаться, "+pchar.name+"! Мы могли бы так славно кутить вдвоём! Ром, вино, красивые девицы... Эх... Удачи в море, капитан!";
			link.l1 = "Я вас так понимаю, caballero! У нас с вами много общего! Но увы - нас обоих ждут дела. Скучные, унылые дела. Желаю вам успехов в тяжбе с дядюшкой, дон Доминго! Уверен - вы победите!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("VOICE\Russian\OliverTrast02.wav");
			dialog.text = "Кажется, я успел как раз вовремя. Мой непутёвый племянник и его ангел-хранитель капитан "+GetFullName(pchar)+"... Да-да, молодой человек, не удивляйтесь - я навёл о вас справки.";
			link.l1 = "Передо мной дон Луис Ортис, как я понимаю?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "Понимаете вы правильно, капитан, но вот поступаете неправильно. Вы напрасно суёте нос в чужие семейные дела. Вы даже не знаете, за кого вступились. Мой племянник Доминго - беспутный повеса, завсегдатай борделей, кабаков, и не пропустит ни одной мало-мальски симпатичной девки. На свои гулянки он спускает всю ренту, что я ему отправляю ежемесячно, и всегда требует ещё. Своим распутным поведением он довёл мою сестру Изабеллу, свою мать, до тяжкой болезни и душевного расстройства!\nДо моих ушей дошли слухи, что именно стараниями этого юного негодника английские каперы напали на судно маркиза Рикардо Альбалате и потопили его, вместе с моей сестрой. Доминго не терпелось получить неограниченный доступ к деньгам семьи... К сожалению, я не смог добыть неопровержимых доказательств, которые, несомненно, отправили бы паршивца на виселицу, но...";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			dialog.text = "Мой дорогой племянник, как обычно - в своём репертуаре. Много крика и шума, звона шпаг и бокалов, но мало толка. Не знаю, чем он вас так подкупил, что вы стали помогать этому недостойному юнцу...";
			link.l1 = "Ха! Не найдя доказательств вины вашего племянника, вы решили совершить самосуд над ним, натравив на него убийц?";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Я? Помилуйте! Ваш друг за недолгое время нажил себе столько врагов - удивительно, что он вообще до сих пор жив. Спросите у него - сколько свадеб он расстроил? Скольких оскорблённых юношей ранил или даже убил на дуэлях?";
			link.l1 = "Вообще-то его слуга Уго...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ах, молодой человек, вы ещё ничего не смыслите в этой жизни! Уго души не чаял в этом выродке, и на все его проделки смотрел, как на невинные шалости. Запомните, кабальеро: лезть в личные дела чужой семьи - неблагодарное дело, и зачастую очень опасное...";
			link.l1 = "Это намёк?.. Или угроза?";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Предупреждение. Вот что, капитан: вы зашли слишком далеко, но поскольку я считаю вас не своим врагом, а всего лишь жертвой заблуждения, то вот вам моё предложение: поворачивайтесь и уходите. Я не желаю кровопролития. Свои семейные дела мы решим как-нибудь без вас. Я готов компенсировать вам ваши расходы, связанные с моим племянником: "+FindRussianMoneyString(iTotalTemp)+" наличными. Берите их и забудьте сюда дорогу. Иначе мои охранники попросту убьют вас.";
			link.l1 = "Кхм... В ваших словах про дела семейные есть резон. Хорошо, я ухожу. Разбирайтесь в своих проблемах сами.";
			link.l1.go = "uncle_7";
			link.l2 = "Может дон Доминго и не ангел, но похоже что вы, сударь, хуже чёрта!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "Вы всё-таки оказались умнее моего племянника. Держите монеты и проваливайте. И впредь постарайтесь не копаться в чужом грязном белье - никто этого не оценит.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			dialog.text = "Я всё понял. Вы ничем не отличаетесь от моего племянника - такой же глупый, вздорный юнец! Пора проучить вас, обоих!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("VOICE\Russian\Serve_senior.wav");
			dialog.text = TimeGreeting()+", сеньор. Чем могу служить?";
			link.l1 = "Здравствуйте. Прошу прощения - это дом сеньора Доминго Альбалате?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Да, это особняк Альбалате, весьма скромный, но очень уютный. Моё имя Уго, и я слуга молодого сеньора. Вы к дону Доминго?";
			link.l1 = "Да, сеньор. Дон Доминго пригласил к себе в гости, и был весьма настойчив. Могу я увидеть его?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Увы, досточтимый кабальеро, дона Доминго нет дома. Я сам бы очень хотел знать, где носит этого шалопая... ох, простите - молодого сеньора... Позвольте полюбопытствовать - кем вы ему приходитесь?";
			link.l1 = "Ну... так получилось, что я помог дону Доминго. В таверне Порт-о-Пренса на него напали две тёмные личности. Я оказал помощь вашему сеньору в ликвидации этих... как он сказал? - dos maldita canalla. После дон Доминго пригласил меня в гости, однако сам был задержан французским офицером для разбирательств. Я думал - он уже всё уладил и вернулся домой...";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "О, ужас! Какие страшные вещи вы рассказываете! Я немедленно должен бежать к коменданту - доложить, что дон Доминго в опасности! Сеньор, вам нужно уйти, а мне - поторопиться!";
			link.l1 = "Успокойтесь, Уго. Вашему молодому хозяину ничего не угрожает. Он сказал, что все документы у него в порядке и его немедленно отпустят. Думаю, он скоро явится домой.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Ох! Да как же вы можете? Мой юный господин, этот наивный мальчуган - в лапах французов! А ещё ему угрожают бандиты! Нет-нет, немедленно к коменданту! Сударь, ступайте, пожалуйста, и позвольте мне пройти!";
			link.l1 = "Хорошо-хорошо, не переживайте вы так. Я ухожу.";
			link.l1.go = "ugo_exit";
			link.l2 = "Сеньор, да что вы так разволновались? Я же сказал - опасности нет. Позвольте мне остаться и подождать сеньора Доминго - я очень устал с дороги, а сами, если хотите, идите на доклад к коменданту.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = "Сеньор, я попрошу вас немедленно покинуть этот дом!";
			link.l1 = "Уго, не думаю, что слуге позволено разговаривать со мной таким тоном! Дону Доминго не понравится подобное обращение с человеком, спасшем ему жизнь!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Ах вот как! Ребята, быстро сюда! У нас проблемы!";
			link.l1 = "Что?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
