// Маркус Тиракс, барон Ла Веги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "А, Принц, неужели явился? Хоть один из вас, наконец, удосужился показаться мне! Дела ждут, а ни тебя, ни Лысого, ни Тесака, ни Лепрекона найти не могу! Где этих охламонов носит, ты не в курсе, случайно?";
					link.l1 = "Нет, не в курсе... Маркус, я пришел сказать, что выхожу из игры. С меня довольно. Мертвецы снятся мне по ночам, и черти с раскалёнными жаровнями мерещатся... Слишком много крови пролилось в последнее время.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "У тебя ко мне дело?";
				link.l1 = "Приветствую, Маркус. Да, дело. Денежное и пиратское.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Принёс деньги?";
				link.l1 = "Да.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "А вот и заказчик пожаловал! Дело сделано, твой барон сидит в подвале под надёжным замком. Не хочешь пойти посмотреть, ха-ха?!";
				link.l1 = "Ещё успею, хе-хе. Его обрабатывают?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Какого дьявола!..";
				link.l1 = "Маркус, накладка вышла. Не смог я прийти, и тебе не сумел сообщить никак...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "А вот и наш кукловод пожаловал!";
				link.l1 = "Ха-ха! Спектакль был отличным!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("У тебя дело ко мне? Нет? Тогда вали отсюда!","Ха, " + pchar.name + "! У тебя дело ко мне? Нет? Тогда не отвлекай меня.") +"",
                         "Я кажется ясно выразился.", "Хотя я выразился и ясно, но ты продолжаешь отвлекать меня!",
                         "Та-а-ак, это уже похоже на грубость, меня это утомило.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Уже ухожу.",
                                               "Конечно, Маркус...",
                                               "Извини, Маркус...",
                                               "Ой...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("У тебя крыша поехала? Вообразил себя мясником? Все пираты злы на тебя, приятель, так что лучше тебе убраться отсюда побыстрее.", "Ты, приятель, похоже, из ума выжил. Руки чесались сильно? Теперь не обессудь - здесь тебе делать нечего. Вали отсюда побыстрее!");
				link.l1 = RandPhraseSimple("Послушай, я хочу исправить ситуацию...", "Помоги мне решить эту проблему...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Маркус, сколько ты будешь злиться на меня? Я вытащил твоего друга Венсана, с которым мы когда-то ходили на Картахену, из лап смерти, да и от тебя беду отвёл, кстати! Или Бернар тебе ничего не рассказывал?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Можно было и помягче, Маркус. Или Бернар тебе ничего не рассказывал про меня?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Я ищу работу... Нет ли у тебя на примете какого-нибудь выгодного дельца?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Я привёз тебе шёлк на продажу.";
				link.l2.go = "Mtraxx_silktrade";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("У тебя крыша поехала? Вообразил себя мясником? Все пираты злы на тебя, приятель, так что лучше тебе убраться отсюда побыстрее.", "Ты, приятель, похоже, из ума выжил. Руки чесались сильно? Теперь не обессудь - здесь тебе делать нечего. Вали отсюда побыстрее!");
				link.l1 = RandPhraseSimple("Послушай, я хочу исправить ситуацию...", "Помоги мне решить эту проблему...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Шарль, какого дьявола!..";
				link.l1 = "Маркус, накладка вышла. Не смог я прийти, и тебе не сумел сообщить никак...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Рад тебя видеть, приятель!";
				link.l1 = "И я тебя. Спасибо за отлично организованный спектакль!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Здорово, приятель! Какими судьбами?";
				link.l1 = "Дело к тебе, Маркус. Пиратское!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "А вот и заказчик пожаловал! Дело сделано, твой барон сидит в подвале под надёжным замком. Не хочешь пойти посмотреть, ха-ха?!";
				link.l1 = "Ещё успею, хе-хе. Его обрабатывают?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "У тебя ко мне дело?";
				link.l1 = "Приветствую, Маркус. Да, дело. Денежное и пиратское.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Принёс деньги?";
				link.l1 = "Да.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "А вот и заказчик пожаловал! Дело сделано, твой барон сидит в подвале под надёжным замком. Не хочешь пойти посмотреть, ха-ха?!";
				link.l1 = "Еще успею, хе-хе. Его обрабатывают?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Какого дьявола!..";
				link.l1 = "Маркус, накладка вышла. Не смог я прийти, и тебе не сумел сообщить никак...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "А вот и наш кукловод пожаловал!";
				link.l1 = "Ха-ха! Спектакль был отличным!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Рад тебя видеть, приятель! Чем я могу тебе помочь?";
				link.l1 = "Маркус, у меня к тебе есть разговор. Не знаю, насколько он будет тебе приятен, но мне так или иначе нужна твоя помощь.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ха, вот и ты, "+pchar.name+". Я ожидал твоего прибытия. Лесной Дьявол озадачил меня твоей проблемой с Тортугой...";
				link.l1 = "Он также сказал мне, что ты, или вы, уже отыскали решение проблемы. Это так?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Я привёз тебе шёлк на продажу.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", рад тебя видеть! Зачем пожаловал"+ GetSexPhrase("","а") +" на этот раз?",
                         "Ну что тебе ещё?", "Долго это будет продолжаться? Если тебе делать нечего, не отвлекай других!",
                         "Ты "+ GetSexPhrase("хороший капер","хорошая девушка") +", поэтому живи пока. Но общаться и разговаривать с тобой я больше не желаю.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да, собственно, просто так заглянул"+ GetSexPhrase("","а") +", проведать. Ничего по делу нет.",
                                               "Ничего, просто так...",
                                               "Хорошо, Маркус, извини...",
                                               "Вот чёрт возьми, доиграл"+ GetSexPhrase("ся","ась") +"!!!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабёж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Пошёл вон","Убирайся") +" отсюда!", "Вон из моего дома!");
			link.l1 = "Ай...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Тебе не стоит отвлекать меня от дела пустыми обращениями. Впредь результат может быть более плачевным...";
        			link.l1 = "Я понял"+ GetSexPhrase("","а") +".";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Ты меня изрядно утомил"+ GetSexPhrase("","а") +", никакого общения.", "Я не хочу с тобой общаться, так что тебе лучше меня не беспокоить.");
			link.l1 = RandPhraseSimple("Ну как знаешь...", "Хм, ну что же...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Надеюсь, впредь ты не будешь утомлять меня пустыми разговорами, иначе мне придётся тебя убить. Признаюсь, мне это будет очень неприятно.";
        			link.l1 = "Маркус, ты можешь быть уверен - не буду...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ха! Так это ты - герой Теркса? Прости за грубый приём, дружище. Бернар мне всё рассказал о твоём чудесном вмешательстве, и что-то там говорил про ловушку для меня. Хотелось бы услышать подробности...";
			link.l1 = "Это и впрямь была западня. Охота была не на Бернара. Охотились за тобой. А Венсан был просто приманкой...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "Расчёт был прост. Предполагалось, что ты сломя голову бросишься спасать своего друга и первым будешь на палубе 'Разлучницы'. В этот момент её должны были взорвать прицельными выстрелами с берега. Бригантину начинили порохом, как булку маком.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Тысяча чертей! Кто удумал такую подлость?! И как бы я узнал, где они прячут Бернара?!";
			link.l1 = "Автор затеи - Джекман и его брат Давид. А сведения о том, что 'Разлучница' ждёт твоей помощи в Южном заливе Теркса, сообщил бы тебе посланник. Этим посланником они выбрали меня, на свою голову.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Ничего не понимаю! Ты-то тут каким боком оказался замешан?";
			link.l1 = "Я давно присматривался к прохвосту Джекману. Я работаю с Яном Свенсоном, если ты не в курсе. Мы с Лесным Дьяволом решили вывести Джекмана на чистую воду. Ян уверен, что в смерти Блейза виновен именно он, а Стивена оклеветали напрасно.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Хех! Но на трупе Блейза был найден акулий зуб с инициалами С.Д. - известная штука, принадлежавшая Стивену...";
			link.l1 = "Его подбросили. Джекман играл по-крупному. Он избавился от Натаниэля Хоука и занял его место в Марун-Тауне, одним ходом устранил и Шарпа, и Акулу. У меня есть неопровержимые доказательства этих злодеяний - в сундуке Якоба я обнаружил половинку карты, принадлежавшую Шарпу, и осколок с орнаментом Натаниэля Хоука.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Чёрт возьми! Так Стивен невиновен? А зачем Якобу всё это понадобилось?";
			link.l1 = "Он рассчитывал встать во главе Берегового братства. И на кое-что ещё, связанное с Исла Тесоро. Ну, а на тебя, как и на Свенсона, он рассчитывать не мог, поэтому решил убрать. Сначала тебя. Яна, как самого крепкого орешка, он оставил 'на потом'.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Где эта сволочь?! Я разорву его на куски!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Джекман мёртв, как и его брат, и остальные охотники тоже. Я лично позаботился об этом. Больше этот мерзавец никому не угрожает. Маркус, ты отдашь свой голос на Совете за Стивена Додсона? Это моя личная просьба.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Джекман мёртв, как и его брат, как и остальные охотники тоже. Я лично позаботился об этом. Больше этот мерзавец никому не угрожает. Но, к сожалению, Стивен был убит...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Конечно отдам! Я всегда считал Акулу самым достойным из нас после Блейза... А ведь я почти поверил в его виновность! Все мы поверили! Вот, возьми мой осколок.";
			link.l1 = "Вот и славно! Теперь ты можешь снять камень с души.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Это точно...  Я так понимаю, ты представляешь интересы Акулы?";
			link.l1 = "Да. Я и Ян Свенсон. Ладно, Маркус, до встречи!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Убит?! Как это случилось? Тоже Джекман постарался?";
			link.l1 = "Нет. В смерти Акулы виновен его боцман, Чад Каппер. Но он своё уже получил... Маркус, Свенсон считает, что ты больше других достоин стать новым президентом Братства. Остальные бароны поддержат это решение. Согласен ли ты занять этот пост?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Хех! Ты ещё спрашиваешь? Быть главой Братства - большая честь! Даже не думай, что я откажусь.";
			link.l1 = "Очень хорошо. Я рад, что ты согласился.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Вот, держи мой осколок. Передай его Свенсону. Как я понимаю, он всем этим занимается?";
			link.l1 = "Да. Именно он. Ладно, Маркус, до встречи!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Да, а за спасение моего друга Бернара я хочу тебя отблагодарить. Вот, возьми этот кошель с золотом.";
			link.l1 = "Не откажусь! Всего доброго!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("Вы получили 300 дублонов");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Да, он мне рассказал про чудесное явление Чарли Принца на Терксе... Говоришь, отвёл от меня беду? И как же, позволь поинтересоваться? Бернар что-то там говорил про ловушку...";
			link.l1 = "Это и впрямь была западня. Охота была не на Бернара. Охотились за тобой. А Венсан был просто приманкой...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ха-ха-ха, ты переметнулся к Лесному Дьяволу, Принц? И как, с его помощью ты заработал больше дублонов и песо, нежели со мной? Ну, признайся честно!";
			link.l1 = "Маркус, давай, наконец, оставим обиды в прошлом. Сейчас у нас общие цели, и они куда более важные, нежели грабежи караванов. На кону стоит судьба всего Берегового братства!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Ладно, Принц, замётано! В конце-концов, ты свободный корсар: решил работать с Лесным Дьяволом - твоё дело, и выбор твой - достойный... Вернёмся к Стивену. Ты сказал - его оклеветали, я не ослышался?";
			link.l1 = "Всё верно.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Ну конечно, чем смогу - тем помогу! Выкладывай, что там у тебя?";
			link.l1 = "Маркус, смотри... Вот акулий зуб. Что ты можешь о нём сказать?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ха! Это зуб белой акулы, которую убил покойный Стивен Додсон, пытаясь понравиться одной красотке. С тех пор его и прозвали Акулой. Мало кому это удавалось сделать под водой при помощи простой сабли. Но он был молод и глуп, а Беатрисс Шарп была самой красивой девушкой на Карибах... Как он у тебя оказался?";
			link.l1 = "Мне отдал его бывший палач Сент-Джонса. Этим зубом зарезали одного человека. Его звали... Джошуа Ледбиттер.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Это старая история. Того человека действительно убил Стивен. Он был потрясён смертью Беатрисс и полагал Ледбиттера единственным оставшимся в живых виновником её смерти. Однако потом он нашёл на его трупе какие-то бумаги, изучил их и раскаялся в содеянном\nМаска не был виноват в смерти Беатрисс - ему нужен был только капитан Бучер. На самом деле всё подстроила ревнивая подруга Бучера, Джессика.";
			link.l1 = "Ты читал эти бумаги?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Что за глупости? Конечно, нет. Зачем они мне были нужны? Но если у тебя есть время, я поведаю тебе, почему Маска преследовал Бучера. Стивен, подвыпив, неоднократно рассказывал мне эту историю.";
			link.l1 = "Время есть. Пойми мой интерес правильно - это не праздное любопытство. Я даже готов записать твой рассказ.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Я знаю, ты напрасно время терять не станешь. Тогда слушай. Джошуа Ледбиттер был английским военным капитаном, и командовал ставшим впоследствии легендарным фрегатом 'Нептун'...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("Прошёл час...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... Ледбиттер же, однако, выжил, и был подобран проходящим судном. Ранение обезобразило его, и отныне он появлялся на людях только в маске на пол-лица - так за ним укрепилось прозвище 'Маска'. Найти и покарать виновника своих бед стало для него единственным смыслом жизни.";
			link.l1 = "Так... Я всё записал. Думаю, что мне потребуется перечитать написанное, чтобы сопоставить с тем, что у меня уже имеется. Действительно, грустная история. А ты видел эту Джессику?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "А как же! Она сопровождала Бучера во всех его походах, до тех пор, пока он не бросил её, увлёкшись Беатрисс. Этого Джесс ему не простила. Её считали талисманом капитана Бучера, потому как пока она была с ним, удача от Бучера не отвернулась ни разу\nХочешь верь, хочешь нет - но как только он её сплавил домой на Барбадос, его дела стали идти всё хуже и хуже - добыча стала скудной, а 'Нептун' буквально прописался на верфи Исла Тесоро. Хотя, это можно объяснить и тем, что Бучер проводил больше времени в каюте с Беатрисс, нежели на шканцах\nВ отличие от Джессики, Беатрисс не имела выраженной склонности к авантюрам и боевым похождениям, хотя Николас обучил её искусству кораблевождения и фехтованию. Конечно, романтика моря её манила, но она не обладала достаточной жёсткостью характера. У Бучера на 'Нептуне' сестра Шарпа была явно не на своём месте. Это в итоге её и погубило.";
			link.l1 = "А Джессика?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "О-о, это была штучка ещё та... Её слушались все матросы на 'Нептуне', и не потому, что она была подругой капитана. Джесс мастерски владела шпагой и прекрасно управлялась с кораблём - школа Бучера не прошла даром. Нрав у неё был крутой и решительный, да и внешностью Бог не обделил\nЖелающих разделить с ней постель было предостаточно, но она никого, кроме Бучера, и знать не хотела, а докучать ей было более, чем рискованно - многие познали это на своей шкуре в буквальном смысле, а для нескольких особо ретивых её урок фехтования оказался последним в жизни\nУ Джесс была особенная шпага, единственная в своём роде на Карибах - уж не знаю, где она такую достала: шпага-фламберж. Её нельзя схватить рукой за лезвие, а даже лёгкое прикосновение оставляет жуткую рану\nДжесс была авантюристкой не по рождению, а по призванию. Кстати, если тебе нужно подробнее узнать о Джессике, ты можешь спросить об этом у одного очень хорошо знакомого тебе человека. Он сможет рассказать о ней побольше, чем я.";
			link.l1 = "Вот как? И кто же этот человек?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Ян Свенсон. Лесной Дьявол, конечно, не признается в этом, но то, что он имел в своё время виды на Джессику - это факт. Он уже тогда прибрал к рукам Западный Мейн, и слава у него была - закачаешься, так что эта тигрица была вполне ему под стать\nКогда Бучер вышвырнул Джесс со своего корабля, Ян подозрительно часто стал появляться на Барбадосе, и так часто, что вызвал немалое беспокойство английского гарнизона. Как ты уже знаешь, Джессика - дочь бриджтаунского плантатора\nВ общем, его планы на неё были хорошо известны в узких кругах, однако высказываться по этому поводу никто бы не рискнул - это сейчас Ян в Блювельде сиднем сидит, а тогда любое неосторожное слово в его адрес могло закончиться плачевно\nНо в итоге у него с ней ничего так и не вышло. Джесс не смогла смириться с тем, как с ней обошёлся Бучер, и спустя год, связавшись с Маской, таки отомстила ему. Эта месть обернулась трагедией для всех: и для Бучера, и для Беатрисс, и для Маски, и для неё самой. Погибли все.";
			link.l1 = "Не все. Бучер жив.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Что?! Я не ослышался? Он жив?!";
			link.l1 = "Да. Капитан Бучер не был казнён. Точнее, был, но благодаря Якобу Джекману и Генри Висельнику, которые запугали палача, остался жив. Казнь была инсценирована. У меня есть доказательства.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Невероятно! И где же Мясник сейчас?";
			link.l1 = "Он известен как Лоуренс Белтроп, и живёт себе спокойно в Порт-Рояле. Однако, похоже, с годами он не стал менее опасен. Джекман, наделавший в последние месяцы столько бед внутри Берегового братства, действовал по его приказам.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Чёрт побери! Квартирмейстер нашёл своего капитана через столько лет! Белтроп, говоришь... постой-ка! Теперь понятно, почему в бумагах Блейза оказался этот странный протокол допроса... Видать, Блейз тоже разузнал о Бучере-Белтропе...";
			link.l1 = "Ты это сейчас о чём?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Когда я занял эту резиденцию, я позволил себе дерзость покопаться в старых бумагах Блейза. Там я нашёл протокол допроса некого Сэмюэля Брукса. Там достаточно подробно описаны похождения Томаса Белтропа - в прошлом известного пирата и близкого друга самого Николаса Шарпа. Очевидно, он и был отцом Бучера.";
			link.l1 = "Очень интересно. Значит, дети Белтропа и Шарпа продолжили дело своих родителей...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Выходит, так... Скажи, дружище, а для чего ты вообще начал копаться в прошлом уже давно умерших людей? К чему весь этот сыр-бор?";
			link.l1 = "Мне нужны бумаги, подтверждающие, что Элен Мак Артур – дочь Беатрисс Шарп, внучка Николаса Шарпа, и имеет право носить эту фамилию. То, что она может носить и фамилию Белтроп, в данном случае меня мало интересует.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "На счёт Элен Мак Артур в архивах Блейза ничего не было. Всё-таки странно, что Беатрисс ничего не сказала Блейзу о рождении племянницы. Это на неё не похоже.";
			link.l1 = "Послушай, может, в бумагах Шарпа было что-то ещё, относящееся к этой истории? Мне важна буквально каждая мелочь!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Хм... Возможно, да. Судя по записям Блейза, он пытался разыскать остров, где погибла его сестра. Есть бумаги, являющие собой копии архивных документов, в которых упоминалась карательная экспедиция Ледбиттера. Там всё пустое, за исключением нескольких цифр, обозначающих географическую широту\nЭта параллель пересекает Карибское море в его северной части. Долготы нет. Очевидно, поиски Блейза успехом не увенчались - ты не представляешь, сколько на этой широте мелких островов.";
			link.l1 = "И что это за широта?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Сейчас посмотрим... вот: 21 гр. 32' северной широты. Не знаю, чем тебе это поможет.";
			link.l1 = "Поможет. Ладно, Маркус, огромное спасибо за откровенный рассказ. Ещё увидимся!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Ну, кое-что я могу для тебя сделать. Как известно, безопасность Тортуги обеспечивает не только форт Ля-Рош, но и постоянно дежурящая у берегов эскадра флибустьеров. Порт Тортуги под надёжной охраной - эти ребята знают своё дело, да и корабли у них мощные. Левассер долго прикармливал этих капитанов\nОни способны противостоять даже линейной эскадре и будут серьёзными противниками при лобовом штурме. Так вот, я, пользуясь своим положением хранителя Kодекса, а теперь - и главы Берегового братсва, сумею увести от берегов Тортуги этих сторожевых псов.";
			link.l1 = "И это всё?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "А разве мало? В любом случае, большего я сделать не могу. Так что штурма форта тебе не избежать, но хоть со сторожевиками не придётся схлёстываться. Уверяю тебя - они ещё опаснее форта, так что моя помощь придётся тебе очень кстати.";
			link.l1 = "Ну что же, раз мне так или иначе предстоит прямая атака - то уход эскадры пиратов будет очень на руку. Спасибо, Маркус! Когда я могу штурмовать Тортугу?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Да когда хочешь. Корабли охранения уйдут по первому моему сигналу.";
			link.l1 = "Ясно. Тогда пойду готовиться к сражению!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "Решить проблему? Да ты сам понимаешь, чего ты наворотил? В общем, принесёшь мне миллион песо - я уговорю ребят, чтобы они забыли твои 'подвиги'. Нет - можешь катиться на все четыре стороны.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Хорошо, я готов заплатить.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Я все понял. Ухожу.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Вот и славно! Считай, что свою репутацию ты восстановил. Но впредь, я надеюсь, ты больше не будешь делать таких мерзостей.";
			link.l1 = "Не буду. Уж очень дорого они обходятся. Прощай...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Сначала кораблём обзаведись, потом о работе спрашивай. Сухопутной крысе у меня делать нечего. Проваливай!";
				link.l1 = "Кхм... Понятно.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Ручки чешутся? Ха-ха! Хорошо... Но предупреждаю тебя, приятель, что спокойной жизни со мной не будет. Если не готов нюхать порох и пускать ручейки красного цвета - лучше проваливай сразу, я на дух не переношу чистоплюев. И также если ты из парней крысиной породы, что любят играть втихую за спиной других и прикарманивать чужую долю - то тебе со мной не по пути, ибо долго ты не проживёшь. Ну так что?";
			link.l1 = "Я готов с тобой работать, Маркус. Звон сабель и пушечные выстрелы меня не страшат, а в отсутствии порядочности ни одна собака упрекнуть не может.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Ого, какой суровый приём! Извини, Маркус, пожалуй, пойду я отсюда...";
			link.l2.go = "Mtraxx_exit";
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "Я что-то не понял: ты ещё здесь?";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ха-ха, ну что же, бравый пират, тогда к делу. Мой источник в Санто-Доминго сообщил мне, что некий испанский капитан хорошо разжился голубым янтарём, да так хорошо, что по пьяни дарит его портовым шлюхам. Ты знаешь, что это такое - голубой янтарь?";
			link.l1 = "Слыхал. Редкий и дорогой камешек.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "В точку, приятель. Даже здесь за него ювелиры да ростовщики отваливают немалые деньги, а в старушке Европе можно выручить в десять раз больше. Янтарь не редкость на Карибах, но вот именно голубой крайне трудно найти. И тут какой-то кастильский проходимец бахвалится, что у него скоро голубого янтаря будет больше, чем желтого у всех ростовщиков Кубы и Эспаньолы, вместе взятых.";
			link.l1 = "Стоит ли верить пьяным россказням испанских краснобаев? Нашел три дублона - а заявил, что отыскал сокровищницу Али Бабы...";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Я бы не верил, если бы он не раздаривал янтарь потаскухам. Так что, как минимум, зерно правды в этой информации есть, а то и целая мерка зёрен. Вот ты и займёшься этим делом. Отправляйся в Санто-Доминго и распутай историю с этим янтарным идальго, а ещё лучше найди его хваленую россыпь. Будет достойный результат - будет тебе награда, почёт и уважение в Ла Веге.";
			link.l1 = "А если вся эта информация окажется не стоящей и гроша?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Тогда принеси мне доказательства того, что этот испанец - лгун и хвастун.";
			link.l1 = "Хорошо. От кого в Санто-Доминго получена эта информация?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Тебе нужна бордельная девка по имени Габриэла Чападо. Назовёшь моё имя и пароль - 'янтарное ожерелье'. Она сообщит подробности. И не теряй времени - информация пока свежая, а вот через день-другой-третий может и устареть.";
			link.l1 = "Всё понял, Маркус. Выдвигаюсь в Санто-Доминго.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "Мне уже рассказали о твоём прибытии. Докладывай!";
			link.l1 = "Разобрался я с этим любителем голубого янтаря, хоть это было и непросто. Удалось разыскать его 'прииск' и неплохо поживиться. Вот добыча: "+FindRussianQtyString(i)+" голубого янтаря.";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("Вы отдали "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" голубого янтаря");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Так-так... Сынок, я же тебя предупреждал насчёт крысятничества, ты помнишь? Что ты мне сказал в ответ? В отсутствии порядочности ни одна собака тебя упрекнуть не может? Ты что, малыш, думаешь, я ничего не проверяю? Да я прекрасно знаю о том, что ты добыл у берега Москитов "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" голубого янтаря. Теперь беги, крысеныш, беги со всех ног, и лучше не попадайся мне!";
				link.l1 = "Проклятье!..";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("Вы отдали "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" голубого янтаря");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Отличная работа, приятель! Ты показал себя с лучшей стороны: распутал сложное дело и честно принёс всё награбленное. Молодец! Рад, что не ошибся в тебе.";
				link.l1 = "Что насчёт моей доли, Маркус?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("Вы получили "+FindRussianQtyString(i)+" голубого янтаря");
			TakeNItems(pchar, "jewelry7", i);
            dialog.text = "Да ты настоящий пират, ха-ха-ха! Половина добычи твоя. Забирай.";
			link.l1 = "Спасибо, кэп. Есть ещё работёнка для меня и моих бравых корсаров?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_SetStat(pchar, 57, 1);
		break;
		
		case "mtraxx_10":
            dialog.text = "Для толковых ребят у меня всегда есть работа. И как раз такому сообразительному парню, как ты, я хочу поручить одно щепетильное дело. В порту Капстервиля уже должен был отдать якорь галеон 'Снэйк' под командованием капитана по имени Джеффри Брук, он же Лысый Джеффри. Это мой человек. Отважный рубака, но в части, что не касается пушек и сабель, тупой, как банник. Впрочем, не будем столь строги к Лысому - нельзя же быть докой во всём, ха-ха!\nТак вот. Этот суровый парень потрепал севернее Синт-Маартена голландский конвой и отбил барк, в котором среди мешков с пшеницей был укрыт солидный груз корабельного шёлка. Это чрезвычайно редкий и дорогой товар на Карибах, голландцы привозят его из Европы ограниченными партиями для нужд своего военного флота. Собственно, на него-то и охотился Лысый Джеффри по моему указанию. Если ты не в курсе, из этого шёлка производят специальные паруса, способные недурственно улучшать ходовые качества судов, поэтому-то на него такой спрос\nКупить его нигде нельзя, а вот продать - можно, да только цена меня не устраивает. Пройдохи-торгаши безбожно занижают его реальную стоимость. Также мне хорошо известно, что есть на Карибах люди, готовые платить за этот товар огромные деньги, причём полновесными золотыми дублонами, однако я до сих пор не удосужился отыскать их. Вот эту задачу я и хочу поручить тебе\nЧто ты так на меня уставился? Грабить караваны любой дурак может, а вот выгодно продать награбленное дано не каждому. Никогда не задумывался, почему работники ножа и топора вечно без гроша в кармане, а скупщики краденого как сыр в масле катаются, а? Если нет, то подумай хорошенько... Впрочем, хватит разглагольствований. Отправляйся в Капстервиль, найди Лысого Джеффри и передай ему, что я приказываю стоять и ждать до тех пор, пока ты не разыщешь покупателя на шёлк. Пусть отправляется в бухту и делает своему корыту кренгование и ремонтирует его\nТы же делай порученное тебе. Ищи покупателя, причём не разового, а с прицелом на будущее - я планирую добывать партии шёлка ежемесячно. И с ценой не прогадай - меньше чем за два десятка дублонов за рулон не торгуйся. Время на поиски у тебя есть, но не бесконечное: держать на суше команду Лысого дольше двух месяцев вряд ли удастся. Всё, бери курс на Сент-Кристофер, да побыстрее, а то не ровен час, Лысый сам продаст шёлк контрабандистам, чем меня очень огорчит.";
			link.l1 = "Кхм... Задачу понял, отправляюсь в путь...";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ха, а вот и "+GetFullName(pchar)+" собственной персоной! Докладывай - что с покупателем?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "Нашёл я покупателя. Это корабел с верфи Порт-Ройяля. Он занимается улучшением ходовых характеристик кораблей и готов покупать его ежемесячно партиями по сто рулонов по цене 25 дублонов за рулон. Товар будут принимать его люди с 10 по 15 число, ночью, на мысе Негрил. Пароль - 'Лионский купец'. Но поиски продлились дольше, чем я предполагал - я не уложлся в отведенные два месяца, и Лысый Джеффри уже наверняка продал шёлк контрабандистам. Уж не взыщи за это строго, Маркус.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Нашёл я покупателя. Это корабел с верфи Порт-Ройяля. Он занимается улучшением ходовых характеристик кораблей и готов покупать его ежемесячно партиями по сто рулонов по цене 25 дублонов за рулон. Товар будут принимать его люди с 10 по 15 число, ночью, на мысе Негрил. Пароль - 'Лионский купец'. Лысый Джеффри уже повёз первую партию на Ямайку.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "Отлично сработано, дружище! Ты меня порадовал. Не так просто найти среди пиратов человека, умеющего работать и головой, а не только руками. Зайди ко мне через двадцать дней - Лысый должен будет привезти деньги за товар, и ты получишь свою долю."; // правки прогона 3
			link.l1 = "Хорошо, Маркус. Скоро увидимся. И подготовь мне ещё какое-нибудь дельце...";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Дело для тебя будет. Всё, до встречи.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Жаль шёлка, конечно, но победителей не судят. Ты проделал хорошую работу, ну а что до шёлка Лысого Джеффри, так ты просто не получишь свою долю от этой сделки, которая тебе причиталась. Но награда всё равно будет - зайди ко мне через месяц, я уже сдам первую партию товара твоему покупателю, тогда и поговорим.";
			link.l1 = "Хорошо, Маркус. Скоро увидимся. И подготовь мне ещё какое-нибудь дельце...";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "Вот и ты, "+pchar.name+". Поговорим о твоей награде.";
			link.l1 = "Такие беседы мне по душе, ха-ха! Внимательно тебя слушаю.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Лысый Джеффри продал твоему покупателю первую партию - 105 рулонов шёлка. Поскольку я рассчитывал на 20 дублонов за рулон, было бы справедливо разницу с цены за первую партию отдать тебе. Так я и решил. Твоя доля составляет 525 дублонов. Также я думаю, что ты заслужил премиальные - ещё по 1 дублону с рулона. Всего ты получаешь 630 дублонов. Держи.";
			link.l1 = "Благодарствую, Маркус!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("Вы получили 630 дублонов");
			PlaySound("interface\important_item.wav");
            dialog.text = "Это ещё не всё. Ты можешь получить дополнительную награду с этого дела.";
			link.l1 = "Интересно... продолжай.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Твой покупатель хочет в ближайшее время взять немного больше, чем по 100 рулонов в месяц, посему если у тебя есть или будет лишний шёлк, можешь привезти его мне. Количество - от 20 до 100 рулонов, срок - в течение двух месяцев, оплата - 24 дублона за рулон.";
			link.l1 = "Хорошо! Если будет, что продать - привезу.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Сколько у тебя товара?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "Очень хорошо. Держи золото, как договаривались - по 24 дублона за рулон.";
			link.l1 = "Благодарствую!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "Я беру 100 рулонов. Держи золото, как договаривались - по 24 дублона за рулон.";
			link.l1 = "Благодарствую!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Вот и славно. Ну, а теперь перейдём к делам насущным. Рвёшься в бой?";
			link.l1 = "А как же! Я и мои ребята готовы к немедленному выходу в море.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Разрази тебя гром, "+pchar.name+", где ты шлялся столько времени? Я когда велел тебе явиться ко мне? Дело, которое я подготовил для тебя, сорвалось из-за твоей непунктуальности. Ты меня очень огорчил, приятель. Проваливай, я не хочу связываться с людьми, на которых нельзя положиться.";
			link.l1 = "Вот это номер...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40) sTemp = ".";
			else sTemp = ", а также торговую лицензию сроком на 40 дней.";
            dialog.text = "Тогда слушай внимательно. Два месяца назад ко мне должен был явиться капитан Жан Пикар, известный у нас как Жан Красавчик. Был должен, но не явился. Поскольку связанный с ним вопрос для меня весьма важен, я выяснил, по какой причине это произошло. Так вот, наш бравый капер умудрился на своей бригантине налететь на испанский тяжёлый галеон под командованием дона Эдуардо де Лосада, а с этим кастильцем шутки плохи. В итоге Красавчик с остатками команды был отвезён в Маракайбо и продан в рабство на местную плантацию. Там он сейчас и гнёт спину\nТвоя задача: прояснить подробности истории, в результате которой Пикар угодил испанцам прямиком в лапы - раз, вытащить его с испанской плантации в живом виде и доставить ко мне - два. В помощь тебе выделяю Пола Чанта, он же Тесак Пелли, вместе с его баркентиной 'Мурена' и всем экипажем. Тесак будет ждать тебя у мыса Раггед-Пойнт, что на Барбадосе. Умом он ушёл недалеко от Лысого Джеффри, но зато весьма сноровист в вопросах сабель и мушкетов. Он будет делать всё, что ты ему прикажешь, не задавая вопросов\nЗаберёшь Пелли с его 'Муреной' с Барбадоса и выдвинешься в Маракайбо, а дальше - по обстоятельствам, учить тебя не надо. Держи десять тысяч песо на дорожные расходы и прочие издержки"+sTemp+". Вопросы есть?";
			link.l1 = "Вопросов нет. Отправляюсь на Барбадос.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
			if (!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) GiveNationLicence(HOLLAND, 40);
            dialog.text = "Тогда желаю удачи. И не теряй времени, не заставляй Тесака и беднягу Жана ждать.";
			link.l1 = "Конечно, босс! Выхожу в море немедленно.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_3", "1");
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "С прибытием, бравый корсар, ха-ха! Расправился с эскадрой кастильцев? Пикар уже обо всём рассказал. Отличная работа!";
			link.l1 = "Да, мои ребята утёрли нос испанцам на выходе из Маракайбо.";
			link.l1.go = "mtraxx_28";
		break;
		
		case "mtraxx_28":
            dialog.text = "По глазам вижу - ждёшь награды. Это справедливо. И оплатит тебе все издержки сам Жан Красавчик - его шкуру спасали. Выставишь ему счёт, какой посчитаешь нужным, но немного позже: сейчас парень без корабля и без денег. Пикар парень мозговитый, вроде тебя, в долгу не останется, я гарантирую.";
			link.l1 = "Кхм... Ладно... подожду. Есть ещё работа для меня, Маркус? И так, чтобы никого не искать и не спасать?..";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Устал быть умником, парень? Я тебя огорчу: тупых головорезов, вроде Тесака, у меня и так хватает, а твои таланты я буду использовать по назначению... Дело для тебя намечается через месяц, а пока отправляйся на Исла-Тесоро к Паскуале Вуазье, купцу в Шарптауне. Это наш человек. Он просил поскорее прислать ему сурового пирата для серьезного дела - скорее всего, для такого, какого ты хочешь: мало думать и много стрелять\nВремени не теряй - через неделю ты Вуазье будешь уже не нужен. И смотри там, не обижай Паскуале - в Береговом братстве его уважают. Всё, ступай, и не опоздай ко мне через месяц, а то я расстроюсь.";
			link.l1 = "Хорошо, Маркус. До встречи!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Ну дела! Покойник всплыл со дна моря! Тебя уже похоронили, приятель, а ты, оказывается, жив!";
			link.l1 = "Как видишь, Маркус...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Тогда что же ты так долго от Маракайбо до Эспаньолы добирался? Я тебя уже со счетов сбросил. Так что извини, дружище: для тебя больше никакой работы нет. Рад видеть тебя в добром здравии, но - бывай!";
			link.l1 = "Эх!.. Как жаль...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35) // опоздал
			{
				dialog.text = "Чёрт тебя дери, "+pchar.name+", где ты шлялся?! Я же сказал - явиться ко мне через месяц! Для тебя было дело на пару с Пикаром, в итоге он отправился в одиночку - не удивлюсь, если из этого похода он не вернётся. Как я могу рассчитывать на тебя в дальнейшем, если ты даже простейших сроков соблюсти не можешь? У меня не армия, но дисциплина должна быть везде! Всё, свободен, нет для тебя больше дел.";
				link.l1 = "Ну и дела...";
				link.l1.go = "mtraxx_33";
				break;
			}
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришел
			{
				dialog.text = ""+pchar.name+", я же сказал - явиться через месяц. Давай, гуляй пока, у меня нет на тебя времени сейчас.";
				link.l1 = "Хорошо...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Человек Вуазье сообщил мне, что ты его 'кинул' на чёрное дерево. Я предупреждал тебя дважды: не обижать Паскуале - раз, и не жульничать с добычей - два. Ты нарушил оба моих правила. Ты сообразительный малый, но с теми, кто обманывает своих товарищей и плюёт на мои указания, мне не по пути. Убирайся к черту и забудь дорогу сюда.";
				link.l1 = "Гхм...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Человек Вуазье сообщил мне, что ты его 'кинул' на чёрное дерево - привёз не весь товар. Если бы это был безмозглый Тесак или Лысый - возможно, я бы и поверил в то, что они и правда захватили не весь груз, но такой умник, как ты... Решил обдурить Паскуале? Я же просил тебя - не обижай его! Нет у меня больше к тебе доверия, и дел у меня с тобой больше тоже нет. Никаких. Проваливай!";
				link.l1 = "Да твой Вуазье сам жулик, каких свет не видывал!.. ";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ха, а вот и бравый капитан Чарли Принц! Если не в курсе - это твоё новое имя в Ла Веге... Ну что, братец, убедился, каково это быть работником ножа и топора? Удача отвернулась от тебя на этот раз, не так ли? То-то же. Вот так и живут мои безмозглые порученцы, вроде Тесака: сегодня кутит в борделе и сыпет дублонами направо и налево, а через неделю клянчит у меня пару тысяч песо на жалование команде таких же безмозглых неудачников. Ладно. Перейдём к делу. Готов?";
				link.l1 = "Конечно!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "А вот и наш бравый капитан Чарли Принц, ха-ха! Человек Вуазье уже побывал у меня. Паскуале тобой доволен. Рад, что ты смог уважить нашего купчину.";
			link.l1 = "Скуповат только наш друг Вуазье оказался...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Ты помнишь мои слова по поводу скупщиков краденого и работников ножа и топора? То-то же. Поэтому нечего тебе мараться об работу, достойную разве что Тесака. Надеюсь, ты учтёшь это на будущее. Ладно. Перейдём к делу. Готов?";
			link.l1 = "Конечно!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Отлично. С минуты на минуту сюда подойдёт Жан Пикар - он и изложит подробности. На дело пойдёте вместе - как раз Красавчику предоставится возможность вернуть тебе должок... А вот и он!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "cartridge", 40);
			LAi_SetCharacterUseBullet(sld, "cartridge");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "В поход с вами пойдёт мой человек - Люка Байярд, более известный в Ла Веге как Люк Лепрекон. Он всю жизнь провёл в лесах Эспаньолы, и джунгли для него - что дом родной. Также к тебе на борт поднимется отряд буканьеров - незаменимые люди в походе через сельву. Дополнишь группу своими лихими рубаками - и Мерида ваша. Себе возьмёшь третью часть добычи, прочее отдашь Жану\nКрасавчик, долг сему бравому капитану за плантацию выплатишь из своей доли на месте, остальное принесёшь мне, дальше разберёмся. Ещё вопросы у кого-нибудь есть?.. Вижу, что нет. Отлично. Лепрекон с буканьерами скоро подойдёт в бухту Ла Веги. Удачи, корсары! Ха-ха!..";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "C возвращением, бравый головорез! Слухи о вашем с Красавчиком Жаном налёте на испанский посёлок достигли Эспаньолы раньше тебя.";
			link.l1 = "Не могу сказать, что сильно рад этому. Лучше сохранять в безвестности такие дела...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Такие дела затихарить не получится, дружище. Ладно. Пикар рассчитался с тобой?";
			link.l1 = "Да.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Очень хорошо. Люком Лепреконом ты остался доволен?";
			link.l1 = "Вполне.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Тогда всё отлично. Все довольны, все при деньгах.";
			link.l1 = "Что ещё для меня есть, Маркус?";
			link.l1.go = "mtraxx_44";
		break;
		
		case "mtraxx_44":
            dialog.text = "Пока ничего. Почти. Достойного тебя дельца, увы, не подвернулось, но имеется моя личная просьба. Выполнишь?";
			link.l1 = "Нет проблем, босс. Какая просьба?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "Уже который день у берегов Ла Веги стоит пинас 'Китти'. Это судно с моим товаром, и ему нужно попасть в Бриджтаун. Пускать в плавание 'Китти' без сопровождения я не хочу - сам понимаешь, почему. Будь так любезен, доведи пинас до Барбадоса в целости и сохранности. Когда вернёшься - думаю, для тебя уже созреет работа. Ну и за сопровождение денег отстегну, конечно.";
			link.l1 = "Договорились.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Вот и славно. Счастливого плавания.";
			link.l1 = "Спасибо!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "А, вот и ты наконец явился... Уже жду тебя. Держи десять тысяч песо за сопровождение 'Китти'.";
			link.l1 = "Спасибо... У меня к тебе разговор, Маркус.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Да неужели?! Ха-ха! Выкладывай!..";
			link.l1 = "Помнишь историю Жана Пикара, как он попал в рабство? Сначала пощипал голландский караван вместе с английским капером, а после дележа добычи сам стал жертвой испанского тяжёлого галеона.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Помню. И?";
			link.l1 = "В Бриджтауне ко мне подошел Игнасио Марко. Это тот самый португалец, капер на службе Англии. Пригласил в таверну и предложил совместно ограбить голландский караван у берегов необитаемого острова, что находится между Кюрасао и Тринидадом.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Так-так... И что ты ему ответил?";
			link.l1 = "Согласился. Во-первых, добыча была заманчивой, а во-вторых, я сразу вспомнил про Пикара и решил разнюхать...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Вижу, что разнюхал.";
			link.l1 = "Точно. Караван был, и мы его взяли - голландцы меняли мачту на своём флагмане, застали их за ремонтом. Потом высадились на берег и приступили к делёжке... но я незаметно отправил на холм дозорного с трубой. И правильно сделал. Потому что вскоре на горизонте появилась испанская эскадра во главе с тяжёлым галеоном.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "И твой компаньон, конечно, успешно слинял, а испанцы погнались за тобой.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Угу. Они на него даже не обращали внимания, все три корабля эскадры нацелились на меня. Однако зря они это сделали: мы преподали испанцам такой урок, что они его надолго запомнят. Хоть кастильцы оказались на редкость умелыми вояками, мы затопили всю их эскадру.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Угу. Они на него даже не обращали внимания, все три корабля эскадры нацелились на меня. Однако мне удалось уйти от них. Но если бы не мой дозорный...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Хех! Одолеть эскадру Эдуардо де Лосада! Да ты просто морской дьявол, Принц! Бьюсь об заклад, испанцы развесили объявление о награде за твою голову в каждой казарме.";
			link.l1 = "Бумага стерпит... А вот с этим шакалом Игнасио надо что-то сделать. Ты понимаешь, о чем я.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Хех! Представляю, как бушевали кастильцы, когда поняли, что упустили тебя! Молодец!";
			link.l1 = "Пусть лопнут от злости. А вот с этим шакалом Игнасио надо что-то сделать. Ты понимаешь, о чем я.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Я займусь этим вопросом. Надо выяснить побольше об этом Игнасио Марко. Действует он сам, или за ним кто-то стоит... Наводит на подозрения его 'внимание' к моим людям. Что за судно у него?";
			link.l1 = "Полакр под названием 'Тореро'. Кораблик необычный, видать, по штучному заказу строился.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Тем лучше, проще отследить будет... Хорошо. Я понял. А для тебя, Принц, у меня есть задание. Готов?";
			link.l1 = RandSwear()+"Конечно, босс!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Тогда принимай вводную. Ещё совсем недавно был у нас на Карибах пират по имени Вульфрик Иогансен, по прозвищу Рыжий Вульф. Явился сюда года два назад с севера Европы. Держался этот викинг особняком, ни с кем дружбы не водил, отстёгивал иногда Левассеру с Тортуги за протекцию, но... в общем, пират-одиночка. Скрытный был до крайности: любой моряк, что попадал на его судно, иначе, как вперёд ногами, оттуда не уходил. Поговаривали, что паре матросов-болтунов, растрепавших в таверне подробности одного похода, Рыжий Вульф лично урезал языки\nВ отличие от большинства пиратов, Иогансен отличался на редкость деловой хваткой: за бесценок награбленное не сдавал, песо и дублоны не спускал в кабаках и борделях. В то же время ростовщикам не доверял и денег у них не хранил. Кораблей не менял, ходил на своём любимом корвете 'Фрейя'. Команде платил очень хорошо, и за службу, и за молчание - спаянный намертво у него был коллектив. Думаю, что намеревался Рыжий Вульф сколотить большое состояние, а затем вернуться в Европу и зажить, как король\nНо, как известно, человек предполагает, а Бог располагает. Попался корвет нашего викинга в лапы испанской карательной экспедиции у берегов Эспаньолы - много крови попортил Вульф кастильцам, крепко злы они на него были. Зажали в бухте на мелководье и разнесли корабль в щепки из дальнобойных орудий, шлюпки спасательные постигла та же судьба, кто из команды не утонул - добили на месте, даже не стали брать в плен, чтобы потом вздернуть на виселице в Санто-Доминго. Таким образом, погиб и Рыжий Вульф, и все его люди\nПоскольку ходили слухи, что свои накопленные богатства Иогансен хранил в корабельном сундуке, то мои молодчики из Ла Веги, охочие до даровой добычи, вдоль и поперёк исследовали место гибели 'Фрейи'. Затонувший остов корабля нашли, ныряли, и сами, и нанятые индейцы - никаких сокровищ нет и в помине. Собственно, я в этом и не сомневался - вряд ли Рыжий Вульф мог оказаться таким простачком. Зато удалось добыть хорошо сохранившийся в плотно запертом сундучке судовой журнал викинга\nИогансен был дотошным во всём и вёл записи подробно и последовательно, вплоть до самого дня своей гибели. И вот теперь мы подходим к сути твоего дела: Вульф несомненно имел приличные богатства - это раз, и их не было на корабле - это два. Значит, он хранил их в каком-то месте, известном только ему и его команде. Увы, у мертвецов не спросишь, но у нас есть журнал. Я почитал его, однако никаких прямых указаний в нем не содержится\nПоскольку ты у нас семи пядей во лбу, то бери этот журнал и постарайся выяснить, где викинг запрятал свои сокровища, награбленные за два года разбоя на Карибах. Так как дело непростое и зацепок, кроме записей в журнале, нет вообще никаких, то в случае успеха тебе достанется две трети найденного.";
			link.l1 = "Гм... Действительно, поиски чёрной кошки в тёмной комнате. Где журнал?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Вот. Держи. Желаю удачи!";
			link.l1 = "Спасибо, она мне понадобится...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "А, наш бравый капитан пожаловал. Что там с сокровищами Рыжего Вульфа?";
			link.l1 = "Работаю над этим. Нужна твоя помощь в этом деле.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Слушаю.";
			link.l1 = "В судовом журнале Вульфрика часто встречается непонятное мне слово 'горд'. Надо выяснить, что оно означает. Тогда, возможно, моё расследование продвинется дальше.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Хм... Горд, говоришь... Я тоже впервые слышу такое слово. Вот что: зайди ко мне через неделю - я поспрашиваю у парочки учёных сухарей, что служат на кораблях счетоводами. Глядишь, что и подскажут.";
			link.l1 = "Хорошо, Маркус. Через неделю.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "Выяснил я твой вопрос. Один книжный червь просветил. Горд - это укреплённый поселок свободного ярла.";
			link.l1 = "Свободного ярла? Кто это?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Это вроде пиратского главы у викингов. Вот я - свободный ярл, а Ла Вега - мой горд. Видать, Рыжий Вульф увлекался историей своих предков, ха-ха! Ну что, помогло тебе это?";
			link.l1 = "Пока не знаю, надо сопоставить записи. Значит, горд - это поселок... Спасибо, Маркус!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "Ну? По твоей торжествующей физиономии вижу, что дело увенчалось успехом.";
			link.l1 = "Да. Клад Рыжего Вульфа найден. Хоть и пришлось прилично попотеть для этого.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "И сколько наш викинг насобирал?";
			link.l1 = "Семьсот пятьдесят тысяч песо и девятьсот дублонов.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Хо-хо! Ты недаром старался, Принц. Что там насчёт моей доли?";
			if (sti(pchar.money) >= 250000 && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = "Вот, держи: двести пятьдесят тысяч и триста золотых, всё по уговору.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Все деньги и дублоны у меня в сундуке на корабле. Сейчас принесу!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Принес?";
			if (sti(pchar.money) >= 250000 && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = "Вот, держи: двести пятьдесят тысяч и триста золотых, всё по уговору.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Да-да, уже несу!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveItems(pchar, "gold_dublon", 300);
			Log_Info("Вы отдали 300 дублонов");
			PlaySound("interface\important_item.wav");
            dialog.text = "Очень хорошо. Ты вообще молодец. Голова!";
			link.l1 = "Маркус, ты выяснил что-нибудь по поводу Игнасио Марко?";
			link.l1.go = "mtraxx_70";
		break;
		
		case "mtraxx_70":
            dialog.text = "Да. Но мне нужно подтверждение или опровержение...";
			link.l1 = "Чего-чего?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "Есть у меня подозрение, что Марко связан кое с кем... И ты это выяснишь. Отправляйся сейчас на Мартинику. Корабль оставь в Сен-Пьере, а сам через джунгли топай в поселок Ле Франсуа. Мне донесли, что наш тип там ошивается. К пиратам с расспросами не приставай, высматривай сам. Найдёшь - проследи за ним: куда пойдет, с кем встретится. И сразу предупреждаю: не вздумай напасть на него самого или его корабль - испортишь мне весь план, который я разрабатываю\nТолько понаблюдай за ним, а потом - сразу сюда, в Ла Вегу. Всё понял? Никакой самодеятельности. Я понимаю, что у тебя руки чешутся, но будь добр - сдержись. А теперь вперёд. Трёх недель тебе должно хватить. Удачи.";
			link.l1 = "Уже в пути, босс.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "Чёрт тебя дери, Принц, неужели нельзя было пошустрее? А ведь можно было и расквитаться с твоим должничком, и очень, очень хорошо заработать! Не ожидал такой непунктуальности от тебя! Ладно, поскольку ты славный парень, я тебя прощаю. У тебя будет шанс реабилитироваться: приходи ко мне через месяц, и желательно на корабле посильнее, но только на одном - и так будет целая эскадра. Я собираю всех своих людей в поход!\nПод моим началом пойдешь ты, Жан Красавчик, Лысый Джеффри, Тесак Пелли, Люк Лепрекон. Всё, пока свободен, жду ровно через месяц, и не вздумай опоздать хоть на день!";
				link.l1 = "Ясно, Маркус. Так уж вышло, но больше не подведу!";
				link.l1.go = "mtraxx_73x";
				break;
			}
			dialog.text = "Вовремя явился! Докладывай, что удалось разнюхать?";
			link.l1 = "Выследил я в Ле Франсуа своего должничка. Его полакр был в составе эскадры, кроме него - корвет и фрегат. Сам Марко заходил к Жаку Барбазону, сидел там долго, часа два, причём в это время охрана никого к Добряку не пускала - всех прогоняли. Затем вышел вместе с двумя угрюмыми типами: один рыжий, бородатый, в рейтарской кирасе и берете, второй усатый, в траншейном доспехе и цветном платке. Все трое пошли в порт, эскадра вышла в море и скрылась прежде, чем я успел добраться до Сен-Пьера.";
			link.l1.go = "mtraxx_74";
		break;
		
		case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 28, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 30, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 31, false);
		break;
		
		case "mtraxx_74":
            dialog.text = "Это неважно. Теперь всё встало на свои места. Эти двое, которых ты видел, люди не то Барбазона, не то Джекмана: работают и у того, и у другого. Такие же умники, как мои Лысый с Тесаком, но вояки наторевшие. У рыжего кличка Бродяга - он капитан корвета 'Каракатица', а усатого прозвали Упырем, он командует фрегатом 'Беспощадный'. Ну а наш друг Игнасио Марко мало того, что подвизался у англичан и испанца дона де Лосада, так ещё и на третью сторону работает - на Барбазона. Поэтому он и подставил Пикара и пытался подставить тебя.";
			link.l1 = "Но зачем ему это было надо?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Заказ Барбазона. Ты не в курсе: Жак Добряк постоянно мелко пакостит мне. На советах Берегового братства всё время лезет на рожон. Открыто враждовать со мной трусит - знает, чем это может для него закончиться, а вот гадить исподтишка - это делает. Он знал, что Красавчик и ты - мои люди, вот и подослал к вам своего наперсника, кстати, совсем не дурака, как ты мог убедиться.";
			link.l1 = "Разберусь с Марко - навещу Барбазона...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Уймись! Ты до Барбазона ещё ростом не вышел. Он тебя перекусит и выплюнет, как акула весло. Мы отплатим ему той же монетой - ударим по его порученцам. И счеты сведём, и Жаку на хвост наступим, и золотом разживёмся, если не напортачим. Готов слушать? Тебя ждёт жаркое дело.";
			link.l1 = "Не впервой!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Игнасио Марко, Бродяга, Упырь и ещё один сподвижник Барбазона, Джокер Джим, под руководством Жака Добряка разработали план, как захватить корабль из золотого флота испанцев, что не так давно прибыл на Кубу из Порто Белло. Мне удалось узнать большую часть этого плана через своих наушников. Один тяжёлый галеон золотого флота задержался в Гаване на верфи, в то время как вся эскадра отбыла в Испанию. Галеон починился и тоже направляется в Европу, вместе с ещё двумя кораблями\nЭскадра пойдёт с Кубы на северо-восток, но вот каким маршрутом - пока неясно. Частично... Мне стало известно, что испанские корабли собирались заходить в Санто-Доминго, потом вдоль берегов Пуэрто-Рико и - в океан. Это же знает и Барбазон\nОднако поскольку Эспаньолу можно обогнуть не только с юга, но и с севера, изменив маршрут, и уйти в океан через Теркс, или Исла-Тесоро, не заходя в Санто-Доминго, Жак решил подстраховаться и отправил хитрого лиса Игнасио в разведку на Кубу, пользуясь тем, что Марко вхож к испанцам\nОстальные трое - Джокер, Бродяга и Упырь, стоят в ожидании у Синт-Маартена, чтобы можно было пойти на перехват как на запад, к Пуэрто-Рико, так и на север, к Терксу и Исла-Тесоро. Марко должен выяснить маршрут следования испанской эскадры и передать информацию на Синт-Маартен. Так как у голландцев с Игнасио свои счёты, а его полакр они знают, как облупленный, заходить в Филипсбург твой друг не станет, а отдаст издалека какие-то сигналы эскадре Барбазона...";
			link.l1 = "Кажется, я уже знаю, что мне предстоит...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Меня радует, что ты такой умный, но всё же слушай дальше. Я вмешался в этот план. При помощи уже известной тебе Габриэлы Чападо из борделя Санто-Доминго, я донёс испанским воякам информацию, что, мол, эскадра пиратов намерена захватить караван из Гаваны у берегов Пуэрто-Рико. Естественно, туда золотой галеон уже не пойдёт, зато пришла и скрытно разместилась мощная карательная экспедиция... Перед тобой стоит целый ряд задач. Первая: найти и захватить полакр 'Тореро'. Что делать с его капитаном - думаю, ясно.";
			link.l1 = "Еще бы!";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "Вторая: выяснить, каким маршрутом пойдёт испанский золотой галеон, где его удобнее атаковать. Это ты наверняка узнаешь либо из журнала Игнасио Марко, либо от него самого. Полученную информацию ты отправишь мне.";
			link.l1 = "Не понял? Каким образом?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "По воздуху. Держи клетку... Это Спайк, почтовый голубь. Он вылупился и вырос в Ла Веге, и вернётся сюда даже с Тринидада. Напишешь записку, привяжешь аккуратно к его лапке и выпустишь. Через несколько часов Спайк будет у меня. Береги этого голубя пуще зеницы ока.";
			link.l1 = "Хех! Ну, босс!..";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Задача третья: отправиться на 'Тореро' к Синт-Маартену. Подчеркиваю: на одном полакре! Иначе люди Барбазона сразу заподозрят неладное. У Синт-Маартена ты отдашь сигнал эскадре Жака Добряка, чтобы они шли к Пуэрто-Рико. Систему сигналов ты тоже должен узнать из бумаг Марко, либо от него лично.";
			link.l1 = "Ясно - ты хочешь отправить Джокера, Бродягу и Упыря прямо в лапы испанским карателям! Хо-хо!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Именно! Так я нанесу удар Барбазону, а сам в стороне останусь. Совсем как он. И последняя, четвертая задача: после передачи сигнала сразу отправишься на перехват эскадры испанцев, и не упусти её! Времени у тебя будет в обрез.";
			link.l1 = "На одном полакре? Против тяжёлого галеона и ещё двух кораблей, причём наверняка не шхун? Да меня разнесут в щепки!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Чего раскудахтался? Даром, что ли, ты мне записку Спайком доставишь? К тебе придёт подмога. Главное - не упусти караван, не дай им удрать в Атлантический океан. Понял?";
			link.l1 = "Понял, босс.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Наградой тебе будет куча золота, да и полакр Марко оставишь себе. Говорят, весьма недурён этот кораблик. Итак, всё ясно, или повторить?";
			link.l1 = "Я не Тесак, понимаю с первого раза. Где перехватывать 'Тореро' - знаешь?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Пока мы тут с тобой распинаемся, он уже летит на всех парусах к Филипсбургу с Кубы. Сейчас должен быть где-то около Тортуги или дальше на восток. Так что не теряй ни минуты - выбирай якоря и дуй со всей силы к Синт-Маартену - лови его на подходе к острову, но не слишком близко! Если люди Барбазона увидят, что ты напал на 'Тореро' - сам понимаешь, плакал мой хитрый план.";
			link.l1 = "Всё ясно. Выхожу в море!";
			link.l1.go = "mtraxx_86";
		break;
		
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "Ну что, Принц, завалил всё дело, так? А?";
			link.l1 = "Да, завалил. Всё оказалось сложнее, чем я себе представлял. Можешь вычитать меня, можешь выставить за дверь.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88":
            dialog.text = "Ладно, не шуми. Бывает. Ты толковый корсар, но неудачи случаются со всеми. Жаль, конечно, испанского золота, но мы его ещё возьмём, не здесь - так в другом месте, ха-ха! У тебя будет шанс реабилитироваться: приходи ко мне через три недели, и желательно на корабле посильнее, но только на одном - и так будет целая эскадра. Я собираю всех своих людей в поход!\nПод моим началом пойдёшь ты, Жан Красавчик, Лысый Джеффри, Тесак Пелли, Люк Лепрекон. Всё, пока свободен, жду в указанный срок, и не вздумай опоздать!";
			link.l1 = "Буду как штык, босс!..";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 18, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 20, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 22, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Хо-хо, приветствую бравого корсара! Не ожидал меня увидеть здесь, да? Ха-ха-ха! Разыскали мы всё-таки испанский караван...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Так точно, босс, разыскали, хотя было это непросто.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Да, вот только испанский золотой галеон затонул вместе со всем грузом.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "Сколько золота мы добыли, Принц?";
			if (iTotalTemp < 1) link.l1 = "Хех... Ничего мы не добыли, босс.";
			else link.l1 = "Хех... "+iTotalTemp+" в весовых мерах...";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Вот незадача! Испанцы выбросили груз за борт, лишь бы нам не достался. Ладно, они своё уже получили, как, впрочем, и люди Барбазона, а это тоже результат.";
				link.l1 = "Жаль золота, конечно... Что дальше, Маркус? В Ла Вегу?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Ерунда какая-то. Ради этого не стоило даже гнать сюда мой корабль с Ла Веги. Очевидно, испанцы выбросили почти весь груз за борт, лишь бы нам не оставлять. Ладно, они своё уже получили, как, впрочем, и люди Барбазона, а это тоже результат.";
				link.l1 = "Жаль золота, конечно... Но поделим хоть это.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "Бедненько, конечно. Едва оправдает расходы на экспедицию. Очевидно, испанцы выбросили часть груза за борт, лишь бы нам не оставлять. Ладно, они своё уже получили, как, впрочем, и люди Барбазона, а это тоже результат.";
				link.l1 = "Жаль золота, конечно... Но поделим хоть это.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Неплохо, хотя я ожидал большего. Очевидно, испанцы всё-таки успели выбросить немного золота за борт, лишь бы нам не оставлять. Ладно, они своё уже получили, как, впрочем, и люди Барбазона, а это тоже результат.";
				link.l1 = "Делим добычу!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Отлично. Мы превосходно сработали, приятель. И люди Барбазона своё получили, ха-ха!";
			link.l1 = "Хех! У нас куча золота! Делим добычу!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... всё как положено в Береговом братстве - пополам. А полакр 'Тореро' - твоя добыча.";
			link.l1 = "Что дальше, Маркус? В Ла Вегу?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4":
            dialog.text = "Я так точно в Ла Вегу, а вот тебя жду у себя через три недели. Желательно на корабле посильнее, но только на одном - и так будет целая эскадра. Я собираю всех своих людей в поход. Под моим началом пойдёшь ты, Жан Красавчик, Лысый Джеффри, Тесак Пелли, Люк Лепрекон. Готовься. Нас ждёт серьёзная экспедиция и немаленькая добыча. Все подробности узнаешь позже.";
			link.l1 = "Хорошо, босс! Буду через три недели в Ла Веге.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "А сейчас бывай, головорез! Ха-ха!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Что-то ещё хочешь сказать?";
			link.l1 = "Нет, пожалуй. Уже отправляюсь на своё судно.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Хех! И кто же в этом виноват, Принц? Не ты ли, часом? Куда ты смотрел?";
			link.l1 = "Босс, извини, конечно, но ты тоже лупил без разбора из своих гигантских кулеврин. Мог бы и поаккуратнее с испанцем...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Ладно. Оба гуся хороши... Одно радует в этой истории - что люди Барбазона своё получили, а это тоже результат.";
			link.l1 = "Жаль золота, конечно... Что дальше, Маркус? В Ла Вегу?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Принц, ты что, стал туго понимать? Я же сказал - явиться только на одном корабле, и так эскадра будет состоять из пяти судов. Живо иди избавляйся от балласта, и назад ко мне! Бегом!";
				link.l1 = "Гм...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Принц, ты что, с Тесака стал пример брать? Зачем ты мне нужен на торговой лоханке? Я рассчитывал на тебя, а ты меня подводишь! Живо беги менять корабль на нормальный, если успеешь до моего отправления - молодец, нет - твои проблемы, ждать никого не намерен.";
				link.l1 = "Гм...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Принц, ты меня удивил. Я же говорил - явиться на корабле помощнее. Чем ты сможешь мне помочь на этой скорлупе? Я рассчитывал на тебя, а ты меня подводишь! Живо беги менять корабль на больший, не ниже третьего класса, если успеешь до моего отправления - молодец, нет - твои проблемы, ждать никого не намерен.";
				link.l1 = "Гм...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Принц, ты бы ещё на королевском 'Повелителе морей' явился. Помощнее - это не значит на линейном корабле. Мы что, против Непобедимой Армады воевать пойдём? У нас в эскадре уже есть один корабль первого класса - мой 'Красный дракон', второй будет только мешать. Живо беги менять корабль на меньший, второй-третий класс, если успеешь до моего отправления - молодец, нет - твои проблемы, ждать никого не намерен.";
				link.l1 = "Гм...";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Рад видеть тебя в добром здравии и вовремя, корсар! Готов к дальнему походу?";
			link.l1 = "Конечно, босс. Как обычно.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "Кстати, тебе не интересно узнать, что стало с эскадрой Барбазона, которую мы отправили к Пуэрто-Рико?";
			link.l1 = "Я как-то совсем забыл о них... Конечно, интересно. Нашли они свою добычу - испанских карателей?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "Нашли. Флагман - фрегат Джокера Джима 'Филин', сгорел дотла. Сам Джокер Джим бесследно сгинул. Бродягу и Упыря крепко потрепали, но они ухитрились сбежать: Бродяга - на Тортугу, под защиту пушек Ля Роша, Упырь - на Исла Тесоро. Паскуале мне рассказал, что Упырь вдобавок усадил на рифы свой корабль недалеко от Шарптауна и еле снялся с них. Мастеру Алексусу теперь предстоит много работы, хе-хе. В общем, немного огорчили меня испанцы. Я думал, что они всех порешат.";
			link.l1 = "Хех. Ничего. Всё равно наступили Барбазону на мозоль. Будет знать, как подсылать своих наперсников.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Это точно. Ладно, теперь к делу.";
			link.l1 = "Слушаю внимательно.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "Как доложила разведка в лице моего бравого боевого товарища Бернара Венсана, испанцы переправили с рудников в глубине Мэйна на побережье огромную партию золотой руды. Там её переплавили в слитки и отскладировали в подвалы форта Картахены, где они ждут очередного 'Золотого каравана' до Европы. Однако золото дождётся не испанских кораблей, а лихих корсаров в нашем лице. Мы идём на Южный Мэйн - штурмовать Картахену.";
			link.l1 = "Аргх! Я не ослышался? Мы будем брать целую испанскую колонию, с фортом?";
			link.l1.go = "mtraxx_95";
		break;
		
		case "mtraxx_95":
            dialog.text = "Со слухом у тебя всё в порядке. Именно это мы и будем делать. Основную ударную силу составит мой военный корабль 'Красный дракон'. Ему по плечу справиться с фортом Картахены. Корабль Лысого Джеффри, ост-индец 'Снэйк' - сменял Лысый свой галеон в бою с голландскими торгашами, напав на них врасплох - повезёт десант. Тесак Пелли наконец избавился от своей позорной баркентины и уселся на подобающее корсару судно - корвет... впрочем, не без моей финансовой поддержки\nПол Чант и ты обеспечите прикрытие от возможных мелких кораблей противника по пути и у самой Картахены. Также ваши команды примут участие в штурме, а такой суровый головорез, как ты, ещё и поможет мне бомбить форт. Жан Пикар, к моему удивлению, не явился, хотя я знаю, что с ним всё в порядке - его корвет 'Грифон' стоит на рейде Порт-Ройяля. Ну, если у Красавчика есть дела важнее испанского золота - это его проблемы, я ждать никого не намерен\nВместо Пикара пятым кораблем в эскадру пойдет Бернар Венсан на бригантине. К нему на борт поднимется Люк Лепрекон с отрядом буканьеров. Этих сил будет достаточно, чтобы сломить сопротивление испанцев и стать хозяевами в Картахене на пару-тройку дней. Мы заберём всё золото из форта и заодно затребуем выкуп с горожан и губернатора. Испанцы надолго нас запомнят, ха-ха-ха!\nА сейчас пока отдыхай, но вечером чтобы был в нашей таверне: прибудут остальные капитаны, и мы все вместе хорошенько выпьем за успех нашего дела. Я прикажу бармену разогнать всю шантрапу - в заведении будем только мы вшестером и девочки. Погуляеешь со своими боевыми товарищами, а завтра с утра - в путь. Встанешь во главе эскадры - будешь прокладывать курс. И постарайся сделать это так, чтобы мы прибыли к Картахене как можно скорее. Всё понятно?";
			link.l1 = "Так точно, босс!..";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		
		case "mtraxx_97":
            dialog.text = "Принц, где ты шляешься, одного тебя ждём! Садись! Уже сидишь? Ну молодец, дружище. Значит, мы можем начинать!\nИтак, бравые корсары! Нас ждёт золото Картахены, ха-ха! И мы его получим, клянусь громом! Но тот, кто умеет хорошо работать, должен хорошо отдыхать! Поэтому сегодня мы чудно проведём время в этом прекрасном заведении. Налейте себе рому, да побольше! Кружки наполнить до краёв! За ветер добычи, за ветер удачи! Пьём до дна!\nБерни, Принц, Тесак, Лысый, Лепрекон! Для вас самое лучшее пойло из погребов нашей таверны, и эти самые прекрасные дамы на острове, ха-ха-ха!.. Корсары, запевай песню! Нашу, любимую!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Итак, корсары, пришло время показать испанцам, кто тут хозяин. Лепрекон! Бери своих людей и отправляйся через джунгли к городским воротам. Городской гарнизон Картахены не должен прийти на помощь защитникам форта. Увидев вас, комендант будет крепить оборону города и не рискнёт отправить подмогу. Когда мы вытесним солдат из форта, ударишь им в спину. Всё понятно?";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = ""+pchar.name+" и Пол! Как вы видели, у берегов Картахены что-то забыла военная испанская эскадра из трех судов. Отправляйтесь и уничтожьте её. Мне свой корабль надо придержать для бомбежки форта - не хватало ещё, чтобы эта мелюзга попортила мне книппелями паруса, а Джеффри надо беречь десант. К форту не лезьте, выманите испанцев от берега подальше. Ясно? Принц, тебя это особенно касается - знаю я твою склонность погеройствовать. Возможность у тебя будет, но позже, со мной на пару\nЯ, Лысый и Бернар ложимся в дрейф и ждём. Как ликвидируете испанские корабли - немедленно возвращайтесь назад. Тут, у бухты Ковеньяс, Тесаку лечь в дрейф, Принцу ко мне на 'Красный дракон.' И ещё: захватывать себе суда испанцев запрещаю - некогда возиться с призовыми лоханками. Только топить. Всем всё понятно? Вижу, что да. Тогда вперёд, корсары, ха-ха-ха!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "Так, с испанской эскадрой покончено. Теперь в дело вступает 'Красный дракон' - пора превратить форт Картахены в груду дымящихся развалин. Готов идти со мной?";
			link.l1 = "Конечно!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "'Красный дракон' очень крепкий корабль с мощной артиллерией, с твоим не сравнится, поэтому на рожон не лезь, приближайся к форту аккуратно и не путайся у меня под орудиями. Вперёд!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Жаркая была схватка! Всё, бравые корсары, Картахена наша. Больше некому сопротивляться, ха-ха-ха! Лысый, Лепрекон! Идете вместе со мной в форт - Берни должен был уже отыскать хранилища с золотом, поможем ему. Принц, бери Тесака и отправляйся на переговоры к губернатору - ты это умеешь, я знаю. Затребуешь выкуп в двести пятьдесят тысяч песо\nГорожане должны собрать откупные - ничего вывезти из города они не могли, буканьеры Лепрекона караулили у ворот. Пускай купцы и прочие богачи раскошеливаются. Будет упорствовать - ты знаешь, что делать, учить не нужно.";
			link.l1 = "Хех! С удовольствием, босс!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "Как успехи, Принц?";
			link.l1 = "Всё отлично. Я заставил раскошелиться богачей Картахены на триста пятьдесят тысяч песо.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Хо-хо, вот это молодец! Но где же деньги?";
				link.l1 = RandSwear()+"Сейчас принесу!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Хо-хо, вот это молодец! Двадцать пять тысяч песо оставишь себе, двадцать пять отдаём Тесаку - это вам обоим премия за смекалку и сноровистость, а триста тысяч давай мне - пойдёт в общий котёл.";
				link.l1 = "Держи!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ну? Прекрати паясничать, тащи монеты!";
				link.l1 = "Уже несу!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Отлично! Двадцать пять тысяч песо оставишь себе, двадцать пять отдаём Тесаку - это вам обоим премия за смекалку и сноровистость, а триста тысяч давай мне - пойдёт в общий котёл.";
				link.l1 = "Держи!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -325000);
            dialog.text = "Тебя, вероятно, беспокоит вопрос, что с нашим золотом? Золото найдено - 5000 весовых мер, и грузится в трюмы наших кораблей. Делёж уже произведён, с ним согласились Лысый, Лепрекон и Берни, надеюсь, что тебя с Тесаком тоже всё устроит.";
			link.l1 = "И какова моя доля?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Поскольку операция задумана и разработана мной, а также поскольку 'Красный дракон' выполнил наиболее важную задачу - разрушение форта, то мне и команде 'Красного дракона' положена половина добычи. Остальное делится между капитанами остальных четырех кораблей, согласно количества их команды. На твоих "+GetCrewQuantity(pchar)+" человек приходится "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" мер золота и "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" песо.";
			link.l1 = "Ну, раз все согласны - чего же я буду возражать? Принято!..";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Прекрасно. Поздравляю, корсары, с успешным походом! Больше нам здесь делать нечего - пора убираться восвояси. Даю всем, в том числе и себе, месяц на отдых от дел. Принц, однако вот тебе будет задание: Жанетта, хозяйка борделя на Тортуге, пожаловалась, что бравый корсар Чарли Принц совсем не балует её заведение своим вниманием. Посему отправляйся на Тортугу, иди к Жанетте и спусти у неё свою премию. Ты это заслужил. Порадуй даму и её девочек. И чтобы без отдыха на Тортуге ко мне не приходил, ха-ха-ха!";
			link.l1 = "Понял, босс. Это самое приятное поручение, которое я когда-либо получал. Будет сделано!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Расходимся, джентльмены! Все на борт своих кораблей и выбираем якоря! Увидимся в Ла Веге!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "Что?!! Жан Красавчик ушёл прислуживать англичанам, два моих придурка - Лысый и Тесак - пропали бесследно, Лепрекон со своими клевретами тоже как сквозь землю провалился, теперь ещё и ты решил дёру дать?!";
			link.l1 = "Маркус, я принял решение. Я хорошо заработал на твоих поручениях, ты тоже с моей помощью получил немало звонких песо и дублонов, но на этом всё. Я ухожу.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "Ты, как и Пикар, решил, что в одиночку тебе больше достанется? Да? Решил, что сможешь всё делать сам, без меня? Поэтому и придумал эту сказку про кровавых мальчиков? Ха-ха-ха! Вали отсюда, Принц, я не собираюсь удерживать тебя. Скоро, очень скоро ты убедишься в ошибочности своего поступка и прибежишь проситься ко мне назад, но я тебя не возьму! Ха-ха! А теперь убирайся с глаз моих!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Хо-хо, тогда ты по адресу! Выкладывай!";
			link.l1 = "Есть один фрукт, который не боится пиратов. Всерьёз их не воспринимает. Надо его поучить уму-разуму. Но не убивать.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Хех! Узнаю старину Шарля! Опять что-то затеял! Ну, давай подробнее, что за фрукт, как учить будем?";
			link.l1 = "Гость из Европы, инспектор министерства финансов барон Ноэль Форже. Хочет организовать тут Французскую торговую Компанию, а я и мой большой друг этого не хотим. Мы пытались убедить барона, что торговать тут весьма опасно из-за голландцев, испанцев, англичан и особенно пиратов, после разгрома Левассера, но он и ухом не ведёт. Надо внушить ему страх, и дать прочувствовать его на своей собственной шкуре.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Хо-хо, тогда ты по адресу! Выкладывай!";
			link.l1 = "Есть один фрукт, который не боится пиратов. Всерьёз их не воспринимает. Надо его поучить уму-разуму. Но не убивать.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Хех! Чего это ты решил впрячься за пиратов? Ладно, если деньги заплатишь, мне всё равно. Давай подробнее, что за фрукт, как учить будем?";
			link.l1 = "Гость из Европы, инспектор министерства финансов барон Ноэль Форже. Хочет организовать тут Французскую торговую Компанию, а я и мой большой друг этого не хотим. Мы пытались убедить барона, что торговать тут весьма опасно из-за голландцев, испанцев, англичан и особенно пиратов, после разгрома Левассера, но он и ухом не ведёт. Надо внушить ему страх, и дать прочувствовать его на своей собственной шкуре.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Так-так... Неужто барон!.. Напасть на его корабль?";
			link.l1 = "План таков: его судно отправляется к Капстервилю из Порт-о-Пренса. Уже скоро. Надо перехватить его у Сент-Кристофера и взять барона в плен. Корабль лучше бы не топить и людей не губить, всё-таки свои, французы... Сможешь?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Это уж как пойдёт, сам знаешь. Но постараюсь. Что за корабль?";
			link.l1 = "Бриг под названием 'Фавори'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Бриг моему 'Красному дракону' не противник. Легко разделаемся. Если сдастся, отпущу всех целыми.";
			link.l1 = "Отлично. Нагони страху и предложи капитулировать. Барона отправишь в трюм к крысам, где пострашнее и погрязнее, но только на день, а то ещё заболеет и умрёт. Потом посели в каюте, доставь в укромное местечко и запри надёжно. К нему надо отправить подсадных уток - твоих людей, которые будут играть роль пленных французских купцов. Пусть они ему дня три рассказывают, как пираты нещадно гоняют торговцев, грабят их и пытают... выкуп требуют... во всех красках.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ха-ха-ха! Такого весёлого дела у меня давно не было! Ну что же, найду таких клоунов. Не сомневайся, после их рассказов твой барон в штаны наложит. Они ему и шрамы от сабель и шомполов раскалённых покажут...";
			link.l1 = "То, что надо. Потом заставишь написать его письмо на имя Пуанси с просьбой о выкупе. Тысяч триста пятьдесят за такую важную птицу много не будет.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Хорошо. Что дальше?";
			link.l1 = "А потом ты привезёшь барона на Теркс. На Терксе передадим выкуп, а ты мне отдашь барона. Плюс скажешь, что за Тортугу и Левассера французы ещё ответят не раз.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ха-ха-ха! Вот это умора! Сами Левассера - того, а теперь... Ха-ха-ха!.. Хорошо, сделаю! Говоришь, скоро кораблик придёт?";
			link.l1 = "Скоро. Но надо уже караулить.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ха-ха-ха! Вот это умора! Сколько же с тебя запросить за эту комедию, а? Ладно, сто тысяч на бочку - и всё сделаю. Деньги вперёд.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Держи.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Хорошо, я принесу.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Отлично! Говоришь, скоро кораблик придёт?";
			link.l1 = "Скоро. Но надо уже караулить.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Не дрейфь, не подведу. Лично займусь этим. Как пройдёт слух, что захватили барона, дуй ко мне.";
			link.l1 = "Хорошо. Спасибо, Маркус.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Конечно, приятель, как договаривались. Страшные истории о злых пиратах, потрошащих невинных французских торговцев. Щёлкание плеткой, вопли и крики. Жаровня с углями и раскалённые наручники. Всё в лучших традициях.";
			link.l1 = "Но-но! Только не переусердствуйте. Он мне живой нужен.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Не дрейфь, жив будет. Письмо он уже дрожащей рукой накалякал. Держи.";
			link.l1 = "Что там написано? Умоляет Пуанси забрать его отсюда?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "В точку - умоляет!";
			link.l1 = "Выброси это письмо, а лучше сожги. Через неделю встречаемся на Терксе. Надо же время типа для сбора выкупа.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Договорились. В заливе Северный через неделю. Деньги не забудь взять: надо, чтобы всё красиво выглядело. Потом ко мне зайдёшь - разберёмся.";
			link.l1 = "Это ясно. До встречи, Маркус!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Эй, лягушатник! А ну, стоять!";
			link.l1 = "Стою.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Вот твой барон, немного потрёпанный, но целый. Он?";
			link.l1 = "Да.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Отлично. А теперь гони деньги, иначе кончим твоего барона прямо тут! И не вздумай хитрить, ты у нас под прицелом!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Держи.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Вот чёрт! На корабле забыл...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ха-ха-ха! А ты молодец, французик. Забирай своё высокопреосвященство. И передай Пуанси, пусть готовит денежки: вы будете теперь долго и дорого платить за то, что сделали с Левассером и Тортугой. И ваши торгаши будут нам платить, товарами и кораблями. Ха-ха-ха! Привозите нам на Архипелаг ещё баронов, за них хорошо платят! Ха-ха-ха!";
			link.l1 = "Барон, идите к моей шлюпке.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "И не вздумай преследовать нас, капитан. Ты знаешь, кто я. У меня в плену ещё три лягушатника, и если я не вернусь домой к сроку - их всех кончат. Понял?";
			link.l1 = "Придёт время, и мы займёмся вами вплотную, проклятые безбожники!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "А-ха-ха-ха!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Ты что, шутить со мной вздумал?";
			link.l1 = "Сейчас принесу...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "А-ать, Маркус, что твой олух наделал!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Шарль, а ты куда смотрел? Где деньги? Я же перед своими дураками всё за чистую монету выдал... этот дурень и решил, что ты хочешь надуть...";
			link.l1 = "Вот неудача! Барон мёртв... Что теперь Пуанси скажет?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "А ты куда смотрел? Где деньги? Я же перед своими дураками всё за чистую монету выдал... этот дурень и решил, что ты хочешь надуть...";
			link.l1 = "Вот неудача! Барон мёртв... Что теперь делать?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Ну, тут ты сам напорол, понимаешь, надеюсь. А может, так и лучше для тебя повернётся - нет человека, нет проблемы.";
			link.l1 = "Да, ну и растяпа же я! Всё испортил. Ладно... Бывай, Маркус.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Ну, дружище, тут ты сам напорол, понимаешь, надеюсь. А может, так и лучше для вас повернётся.";
			link.l1 = "Да, ну и растяпа же я! Всё испортил. Ладно, пойду к Пуанси... Бывай, Маркус, и прости дурака.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Тебе надо отдохнуть - ты теряешь хватку. Заходи в гости, я тебе девок и рому организую.";
			link.l1 = "Спасибо, загляну как-нибудь.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Не за что, дружище. Для меня это было лучшим развлечением за последний год! Мы тут с ребятами так нагоготались!.. Так что это тебе спасибо, повеселил на славу. Держи свои деньги.";
			link.l1 = "Думаю, что тебе должна причитаться их часть.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Держи свои деньги, интриган. Ха-ха! Забавное было дельце.";
			link.l1 = "Спасибо за помощь, Маркус. Удачи!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Брось. Это по дружбе. Ты сделал для Берегового братства в разы больше, и не попросил ни дублона.";
			link.l1 = "И всё же возьми пятьдесят тысяч компенсации за издержки. Спасибо, Маркус";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Не за что. Заходи в гости, как время будет!";
			link.l1 = "Обязательно!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Мы тебя ждали неделю! А я своим дуракам всё за чистую монету выдал! И в один прекрасный момент они просто кончили твоего барона!";
			link.l1 = "А-ать! Что же я теперь Пуанси скажу? Вот растяпа я!";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "Тебя ждали неделю! А я своим дуракам всё за чистую монету выдал! И в один прекрасный момент они просто кончили твоего барона!";
			link.l1 = "А-ать! Что же я теперь Пуанси скажу?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Ну, дружище, тут ты сам напорол, понимаешь, надеюсь. А может, так и лучше для вас повернётся.";
			link.l1 = "Ладно, пойду к Пуанси... Бывай, Маркус, и прости дурака.";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Это твои проблемы, сам напорол. Надо было делать всё по уговору.";
			link.l1 = "Ладно... Бывай, Маркус.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Тебе надо отдохнуть - ты теряешь хватку. Заходи в гости, я тебе девок и рому организую.";
			link.l1 = "Спасибо, загляну как-нибудь.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
	}
}