// Джаспер Пратт - каторжник
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
				dialog.text = "Здравствуйте, мистер. Вы что-то хотели?";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+", а вас как? Я просто недавно тут, вот, знакомлюсь...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Вы что-то хотели?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать вам пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у вас дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Я? Я - Джаспер, бывший каторжник. Из-за этого многие смотрят на меня косо. Ну да и чёрт с ними, я привык...";
			link.l1 = "Мне абсолютно всё равно, кем вы были раньше. Главное - кто вы есть сейчас.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Жаль, что не все считают так, как вы, мистер.";
			link.l1 = "Ну, я всегда отличался либеральностью взглядов...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Рад за вас. Смею уверить, что несмотря на моё неудавшееся прошлое, никакой угрозы кошелькам и сундукам обитателей Острова я не представляю. Я просто рад, что могу наконец-то спокойно жить.";
			link.l1 = "Будем знакомы, Джаспер! Ещё увидимся!"
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Я хочу задать вам пару вопросов об острове.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Да, конечно. Отвечу, если буду знать. Спрашивайте.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Как вы стали жителем Острова?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Как вам здесь, на Острове?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Вы говорили, что на вас смотрят косо. Это всё из-за вашего прошлого?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Интересно устроен этот Остров, не находите?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Бежал с каторги с плантации Кубы. Нас было пятеро, и мы решили, что лучше умереть, чем продолжать горбатиться и получать бесконечные побои. Мы смогли обмануть охрану и скрыться в джунглях, добрались до побережья, связали плот из бамбука и вышли в море\nМы хотели доплыть до Тортуги, но судьба распорядилась иначе. Никто из нас не умел толком ориентироваться, и мы оказались затерянными посреди моря и гребли наудачу. Потом закончилась вода... Я не хочу об этом вспоминать. В итоге, до Острова добрался только я один, и то, чудом выжил.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Вы знаете, я не жалуюсь. После того, что я пережил на плантациях сахарного тростника, да и того, как я жил раньше - здесь просто рай земной. Мне ведь много не надо... Немножко еды, немножко воды и кружка рому по вечерам. Меня никто не беспокоит, здесь я наслаждаюсь покоем, и никуда отсюда не уеду. Здесь же и умру, когда придёт моё время.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Дело в том, что на Острове орудует таинственный вор. Для него ни один замок не является преградой - он проникает всюду. Но в основном он любит пошастать по кладовой адмирала. Хотя и по нашим сундукам он тоже шарится. Кто этот воришка - неизвестно, вот и подозревают всех, у кого прошлое... гм, не безупречное\nОднако вор очень странный: во-первых, всегда запирает сундук, в который залез, а во-вторых, берет только бутылки со спиртным да всякую ерунду, а ценные вещи не трогает. Забавно, правда?";
			link.l1 = "Это точно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Да, согласен. Я много плавал вокруг внутренних кораблей Острова. Подняться из воды можно только в нескольких местах: на 'Сан-Августин' к висячему мосту, на 'Глорию' по поваленной мачте. Также, если проплыть к платформе 'Феникс' и обогнуть 'Сан-Габриэль', можно забраться на носовую часть флейта 'Церес Смити', прямиком в каюту к Мэри Каспер\nЧерез разлом на 'Тартарусе' - попадёте в нижнюю часть тюрьмы. Также можно забраться через повреждённую часть корпуса 'Сан-Августина' в носовую часть, где дверь в кладовую адмирала, но лазить туда я категорически не советую - сочтут за вора, и тогда не миновать беды. Нижнюю дверь 'Тартаруса' тюремщик частенько закрывает, имейте это в виду\nНу и, конечно, можно залезть на 'Фернанду' - это треснувший напополам флейт, стоит отдельно от всех прочих кораблей. Там вроде как никто не живёт, но готов поклясться, что это не так: в последнее время я частенько замечаю там в каюте мерцающий свет, как от свечи, да ещё иногда слышны какие-то пьяные песни и возгласы.";
			link.l1 = "Очень интересно... Надо поисследовать все эти места.";
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