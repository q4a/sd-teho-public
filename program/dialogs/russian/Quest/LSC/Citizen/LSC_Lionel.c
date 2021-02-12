// Лайонел Маскетт - мещанин
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Приветствую, "+GetAddress_Form(NPChar)+". Вы у нас недавно?";
				link.l1 = TimeGreeting()+". Моё имя - "+GetFullName(pchar)+". Да, можно и так сказать...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Вы что-то хотели?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать тебе пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у вас дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Меня зовут Лайонелл Маскетт. Будем знакомы. Как вы добрались до Острова?";
			link.l1 = "На баркасе... Вот, услышал, что тут есть какая-то таинственная база контрабандистов - дай, думаю, разведаю... Вот и разведал. Баркас на дне, а сам я - здесь.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Что, прямо так про нас и считают - база контрабандистов?";
			link.l1 = "Ну, не то что бы это была официальная точка зрения. Большинство на Карибах в ваше существование вообще не верит.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Да уж... А чего в нас верить-то? Нас, почитай, и нет. Кто попал сюда - уже не выбирается. Хотя раньше, говорят, была связь Острова с Кубой... Но это было ещё не на моей памяти, а живу я здесь без малого восемь лет.";
			link.l1 = "Понятно. Приятно было поболтать. Ещё увидимся!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Я хочу задать вам пару вопросов об острове.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Внимательно вас слушаю.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Как вас занесло на этот Остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "А вы бы хотели вернуться в большой мир?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "И чем же люди занимаются здесь, на Острове?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "А откуда берётся здесь всё на Острове? Еда, одежда, выпивка?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Это странная история. Сей Остров - единственное место, которое я видел на Карибах. Когда меня допекла нужда, я отбыл из старушки Англии на торговом судне в колонии. Я собирался устроиться в Белиз в портовое управление служащим. Но до Белиза мы так и не добрались\nЯ не моряк, и не знаю всех подробностей - просто однажды налетел сильный шторм, а спустя почти сутки ночью наш корабль наскочил на рифы. Я никогда не забуду этот ужасный удар и леденящий душу скрежет\nПоднялась паника, крики - 'пробоина, тонем'! Все попрыгали за борт. А я... не умел плавать, и остался сидеть в своей каюте. Как ни странно, но судно не затонуло, а шторм унялся с рассветом\nЯ вышел наружу, осмотрелся и принял единственно верное решение: взял с собой мешок сухарей, спустил на воду обломок какой-то реи и доплыл по тихому и мирному морю до внешнего кольца кораблей, а потом уже и сюда. Так я и спасся - единственный из всей команды.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Первые два года я только и мечтал об этом. Но теперь... А чем этот Остров хуже любого другого места? Да, здесь нет зелёных полей с пасущимися овцами, но зато есть великолепное море и небо со звёздами неописуемой красоты. Я сыт, у меня хорошая одежда, чего в Англии мне так недоставало, есть друзья\nНет, сэр, я никуда не хочу уезжать отсюда. Что меня ждёт там? Работа на крикливого чиновника за три сотни песо в неделю? Нет уж, увольте! Я нашёл здесь всё, что искал, и более мне ничего не нужно.";
			link.l1 = "Понятно. Рад за вас!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Кто чем. Кланы играют в войну, пираты торгуют провиантом, Аксель Йост скупает и перепродаёт всякий хлам, Санчо Карпентеро наливает ром и всех развлекает, брат Юлиан молится, служит обедню и продаёт лекарства. Лодердэйл и Сольдерра плетут интриги друг против друга, Маскетт пьёт, Эббот надувается от важности, а Джиллиан и Таннеке мечтают о большой любви...";
			link.l1 = "Очень занятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "С кораблей, друг мой, с кораблей. Любимое занятие большинства жителей Острова - исследование лоханок внешнего кольца и добыча с них всяких вещей. Там можно найти всё, от оружия и медикаментов до пряностей и рома. Многие корабли и по сей день не исследованы. Да и течение периодически прибивает к Острову очередную жертву...";
			link.l1 = "Интересно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдёт!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдёт!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьёзному мужчине...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял.", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}