// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        // --> Страж истины
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
        {
            dialog.text = "О! Здравствуйте, сударь. Как вы сюда попали?";
            link.l1 = "Здравствуй, Джино. Давай познакомимся. Я - капитан " + GetFullName(pchar) + ", и поднялся в твою комнату с разрешения Джона. Сразу оговорюсь - я пришёл за помощью, но... также и для того, чтобы помочь тебе.";
            link.l1.go = "guardoftruth_0";
            npchar.quest.meeting = "1";
            break;
        }
        if (npchar.quest.meeting == "0")
        {
            dialog.text = "О! Здравствуйте, сударь. Как вы сюда попали? А где Джон?";
            link.l1 = "Так-так... Вот кто скрывался за этой запертой дверью! Очень интересно... Касательно Джона - то он... уехал. И этот дом теперь принадлежит мне. Но ты не волнуйся. Давай познакомимся: кто ты, и что здесь делаешь?";
            link.l1.go = "meeting";
            npchar.quest.meeting = "1";
        }
        else
        {
            // --> Страж истины
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
            {
                dialog.text = "Здравствуйте, " + pchar.name + ". По вашему выражению лица я вижу, что вы хотите сказать мне нечто важное. Неужно нашли все компоненты Стража Истины?";
                link.l1 = "Именно! Все три предмета: дага, карта и компас у меня!";
                link.l1.go = "guardoftruth_34";
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
            {
                dialog.text = "Здравствуйте, " + pchar.name + ". Что-то случилось? У вас какой-то странный вид...";
                link.l1 = "У меня к тебе разговор, Джино. Важный разговор.";
                link.l1.go = "guardoftruth";
                break;
            }
            // Ксочитэм
            if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
            {
                dialog.text = TimeGreeting() + ", " + pchar.name + ". Да, я помню: два дня прошли, и вы хотите узнать, что там со Стражем Истины, так?";
                link.l1 = "Конечно! Тебе удалось что-нибудь раскопать?";
                link.l1.go = "ksochitam";
                break;
            }
            //--> Португалец
            if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
            {
                dialog.text = "Вы принесли 5 000 песо, " + pchar.name + "?";
                if (sti(pchar.money) >= 5000)
                {
                    link.l1 = "Конечно. Вот, держи деньги и купи всё, что тебе требуется.";
                    link.l1.go = "Portugal_3";
                    SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 3, false);
                    DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
                    pchar.quest.Portugal_Ill1.over = "yes";
                    pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
                    pchar.quest.Portugal_Ill.win_condition.l1.date.hour = sti(GetTime());
                    pchar.quest.Portugal_Ill.win_condition.l1.date.day = GetAddingDataDay(0, 0, 4);
                    pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 4);
                    pchar.quest.Portugal_Ill.win_condition.l1.date.year = GetAddingDataYear(0, 0, 4);
                    pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
                }
                else
                {
                    link.l1 = "К сожалению, у меня сейчас нет денег.";
                    link.l1.go = "Portugal_nomoney";
                }
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
            {
                dialog.text = "Увы, " + pchar.name + ", мне очень жаль - больной умер. Ему внезапно стало хуже и он быстро скончался.";
                link.l1 = "Действительно жаль... Да смилуется Господь над его душой!";
                link.l1.go = "exit";
                DeleteAttribute(pchar, "questTemp.Portugal.Die");
                pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
                pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
                pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
                AddQuestRecord("Portugal", "6");
                CloseQuestHeader("Portugal");
                pchar.questTemp.Portugal = "end";
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
            {
                dialog.text = "Здравствуйте, " + pchar.name + ". Что-то случилось? Вы выглядите взволнованным...";
                link.l1 = "Джино, у меня к тебе необычная просьба! На моём судне человек в лихорадке. Он бредит, и совсем не приходит в сознание... ты можешь помочь?";
                link.l1.go = "Portugal";
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
            {
                dialog.text = "" + pchar.name + ", я жду вашего больного. Чем быстрее вы его доставите - тем больше шансов, что его удастся спасти.";
                link.l1 = "Да-да, его сейчас доставят.";
                link.l1.go = "exit";
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
            {
                dialog.text = "Вы вовремя его доставили, " + pchar.name + ". Состояние критическое, но я думаю, шансы у нас есть\nКапитан, у меня на исходе некоторые ингридиенты для настоек, а идти самому собирать нужное в джунглях совершенно нет времени. Нужно приобрести всё у местного травника - мне необходима сумма в 5 000 песо. Вы можете мне её предоставить?";
                if (sti(pchar.money) >= 5000)
                {
                    link.l1 = "Конечно. Вот, держи деньги и купи всё, что тебе требуется.";
                    link.l1.go = "Portugal_3";
                    SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 3, false);
                }
                else
                {
                    link.l1 = "К сожалению, у меня сейчас нет денег.";
                    link.l1.go = "Portugal_nomoney";
                    pchar.quest.Portugal_Ill.over = "yes";
                    pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
                    pchar.quest.Portugal_Ill1.win_condition.l1.date.hour = sti(GetTime());
                    pchar.quest.Portugal_Ill1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
                    pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
                    pchar.quest.Portugal_Ill1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
                    pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver"; //не принесет через 1 день - Португальцу капут
                }
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
            {
                dialog.text = "Пока ничего не могу сказать, " + pchar.name + ". Я борюсь за жизнь пациента. Надежда есть. Зайдите позже, думаю, скоро я смогу сказать вам что-то определенное.";
                link.l1 = "Хорошо, Джино, загляну через некоторое время.";
                link.l1.go = "exit";
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
            {
                pchar.quest.Portugal_Ill.over = "yes";
                dialog.text = "У меня есть новости, " + pchar.name + ". Не скажу, что с вашим человеком всё в порядке, но жить он будет. Болезнь отступает, и прогресс налицо. Честно сказать, я и не думал, что мои средства окажут такое воздействие.";
                link.l1 = "Это всё очень интересно, Джино, но скажи мне, когда я смогу его забрать? Нам предстоит неблизкий путь, а время уходит.";
                link.l1.go = "Portugal_4";
                break;
            }
            if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
            {
                dialog.text = "Здравствуйте, капитан. Рад вас видеть.";
                link.l1 = "Как там наш пациент, Джино?";
                if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2)
                    link.l1.go = "Portugal_9";
                else
                    link.l1.go = "Portugal_threedays";
                break;
            }
            // <--Португалец
            dialog.text = "Добрый день, капитан. Как у вас дела? Требуется моя помощь?";
            if (!CheckAttribute(npchar, "quest.rome"))
            {
                link.l1 = "Да. Джино, ты как я понимаю, учёный человек, и даже знаешь латынь, наверное...";
                link.l1.go = "rome";
            }
            if (CheckCharacterItem(pchar, "chemistry"))
            {
                link.l2 = "Тут немного другое. У меня для тебя небольшой подарок. Вот, посмотри на эту книгу.";
                link.l2.go = "chemistry";
            }
            if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
            {
                link.l2 = "Да, Джино. Я хочу показать тебе вот этот пистолет. Видел ли ты когда-нибудь что-то подобное?";
                link.l2.go = "colt";
            }
            if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
            {
                link.l2 = "Я принёс образец заряда для моего пистолета.";
                link.l2.go = "colt_1";
            }
            if (CheckAttribute(npchar, "quest.cartridge"))
            {
                link.l2 = "Что насчёт зарядов к пистолету? Удалось что-нибудь понять?";
                link.l2.go = "cartridge";
            }
            // Addon 2016-1 Jason Пиратская линейка
            if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
            {
                link.l3 = "Джино, в записях одного капитана постоянно упоминается непонятное слово 'горд'. Не мог бы ты разъяснить мне, что это такое?";
                link.l3.go = "mtraxx";
            }
            link.l9 = "Здравствуй, Джино. Дела - нормально, со всем справляюсь пока сам. Просто зашёл проведать тебя и поговорить.";
            link.l9.go = "exit";
        }
        NextDiag.TempNode = "First time";
        break;

    case "meeting":
        pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
        dialog.text = "Меня зовут Джино. Джино Гвинейли. Я учёный. Занимаюсь тем, что готовлю порошки, микстуры и прочие лекарства для нужд мистера Мердока. Но раз теперь он уехал, то...";
        link.l1 = "Ну а я - " + GetFullName(pchar) + ". Капитан собственного корабля. Значит, ты - алхимик?";
        link.l1.go = "meeting_1";
        break;

    case "meeting_1":
        dialog.text = "Не только алхимик, но также и лекарь. У меня неплохие познания в медицине. Знаю свойства лечебных трав и умею готовить из них отвары, настойки и микстуры. Но моё призвание - познание химической природы веществ, я постоянно экспериментирую и открываю новые и новые соединения, которые могут оказаться очень полезными, в том числе и для вас\nЗнаю латынь, английский, французский и итальянский языки. Если вы собираетесь, как и мистер Мердок, вести аптечное дело - вам без моей помощи не обойтись...";
        link.l1 = "Ого! Не каждый день встречаешь столь учёного человека. Аптечное дело - это, конечно, хорошо, но я моряк... кхм, как необычно звучит для самого... однако я совершенно уверен в том, что мы поладим, Джино. Ты будешь спокойно, как и раньше, жить в этом доме и заниматься своей наукой...";
        link.l1.go = "meeting_2";
        break;

    case "meeting_2":
        dialog.text = "";
        link.l1 = "А если мне понадобится помощь алхимика, лекаря или просто учёного человека - я буду знать, к кому обращаться, и далеко идти не потребуется... Скажи, а почему ты постоянно живешь взаперти? Ты даже не выходишь в город?";
        link.l1.go = "meeting_3";
        break;

    case "meeting_3":
        dialog.text = "Ну почему же... выхожу, когда мне нужно купить трав или каких-то ингредиентов для моих опытов. А живу затворником... мне так нравится. Я посвятил свою жизнь науке, и мирская суета меня мало интересует. Мне больше нравится проводить всё своё время в окружении моих книг, рукописей, пробирок, колб и реторт\nМистер Мердок предоставил мне такую возможность в обмен на мою помощь в приготовлении лекарств. Часть своего дня я посвящал работе на мистера Мердока, а оставшееся время у меня уходило на научные исследования.";
        link.l1 = "Теперь у тебя его будет ещё больше, Джино. Но если мне потребуется твоя помощь - то тебе придётся поступиться своим временем, которое ты тратишь на свои эксперименты, договорились?";
        link.l1.go = "meeting_4";
        break;

    case "meeting_4":
        dialog.text = "Безусловно, капитан. Я буду звать вас 'капитан', " + GetAddress_Form(NPChar) + ", хорошо? Как только вам потребуются мои практические навыки или теоретические знания - я оставлю все свои исследования и буду заниматься только вашими делами.";
        link.l1 = "Прекрасно. Я рад, что мы так быстро нашли общий язык. Насчёт своего пансиона не беспокойся - я или мой казначей будем периодически оставлять тебе достаточные суммы денег.";
        link.l1.go = "meeting_5";
        break;

    case "meeting_5":
        dialog.text = "Спасибо, капитан. Мне много не нужно... Да, капитан, я тут подумал... а не хотите ли вы тоже немного приобщиться к искусству алхимии? Это вам может очень и очень пригодиться.";
        link.l1 = "Хм. Как говорил мой братец - не стоит брезговать научиться делать что-либо собственными руками. Конечно, хочу. А что ты можешь мне показать?";
        link.l1.go = "meeting_6";
        break;

    case "meeting_6":
        dialog.text = "Ну, конечно, превратить железо в золото у вас не получится - впрочем, это пока ещё никому не удалось - но смешивать ингредиенты согласно рецептам и получать на выходе зелья и другие полезные предметы вы точно сможете. Вот, возьмите этот саквояж. В нем есть всё, что нужно начинающему алхимику - пробирки, колбы, реторты, перегонный куб, шпатели, стеклянные трубки, горелка и прочее...";
        link.l1 = "Как интересно!";
        link.l1.go = "meeting_7";
        break;

    case "meeting_7":
        Log_Info("Вы получили набор алхимика");
        GiveItem2Character(pchar, "alchemy_tool");
        PlaySound("interface\important_item.wav");
        dialog.text = "Для того, чтобы приготовить собственное зелье или предмет, вы должны знать его рецепт. Рецепты вы можете купить у торговцев травами и амулетами, или найти где-либо ещё. Затем, изучив рецепт, вы должны собрать все нужные ингредиенты и выполнить действия в строгой последовательности, как указано в рецепте\nЕсли вы собираетесь приготовить зелье - вам потребуется пустой пузырёк, чтобы поместить туда приготовленное. Для нагревания используйте горелку, для взятия навесок веществ - шпатель, для простого кипячения - колбу, для испарения с конденсацией - перегонный куб\nТакже вам наверняка потребуется ступка и пестик для измельчения твёрдых компонентов, но эти предметы вы сможете приобрести у лоточников за приемлемую цену. Также вам может понадобиться тигель - для нагревания веществ до очень высоких температур - но лишнего тигеля у меня сейчас нет\nТак что если вам вдруг попадётся такая штука, берите даже не думая - пригодится. В общем, надо пробовать, пытаться - и все получится. Компоненты - это как правило травы, спиртосодержащие жидкости, готовые зелья, минералы, а также вообще любые предметы.";
        link.l1 = "Ясно. Буду пробовать на досуге. Спасибо, Джино! А хоть какой-нибудь простенький рецепт ты мне можешь дать? Чтобы я сразу приступил к практике?";
        link.l1.go = "meeting_8";
        break;

    case "meeting_8":
        dialog.text = "Простых у меня нет... но вот, возьмите вот этот рецепт противоядия. Думаю, вы вполне сможете справиться с данной задачей. Держите.";
        link.l1 = "Благодарю! Буду потихоньку учиться. Ну а пока - до встречи, Джино! Присматривай за моим домом - боюсь, я тут буду бывать нечасто, так что смело распоряжайся не только в своей комнате, но и за её пределами. Увидимся!";
        link.l1.go = "meeting_9";
        break;

    case "meeting_9":
        DialogExit();
        GiveItem2Character(pchar, "recipe_potion3");
        Log_Info("Вы получили рецепт противоядия");
        PlaySound("interface\notebook.wav");
        Log_Info("Для создания собственных зелий и амулетов вы должны владеть навыком 'Алхимия'!");
        NextDiag.CurrentNode = "First time";
        break;

    case "rome":
        dialog.text = "Да, капитан, я изучил язык древних римлян. Каждый учёный, особенно лекарь или алхимик, обязан знать латынь. Вам нужно что-то из моих познаний в латыни?";
        link.l1 = "Да. Джино, не сочти меня за глупца, но... как тебе лучше объяснить...";
        link.l1.go = "rome_1";
        break;

    case "rome_1":
        dialog.text = "Говорите как есть, капитан. Не стесняйтесь.";
        link.l1 = "Хорошо. Не мог бы ты мне составить список учёных латинских изречений? Понимаешь, есть тут у меня один... человек, который любит хвалиться своей 'учёностью', и время от времени в разговорах вворачивает латинские фразочки, дабы показать, какой я неуч по сравнению с ним. Ну, что-то вроде, 'пасем-беллум'...";
        link.l1.go = "rome_2";
        break;

    case "rome_2":
        dialog.text = "'Си вис пасем, пара беллум', вы хотели сказать?";
        link.l1 = "Вот-вот. Я хочу выучить их и при случае утереть нос заносчивому бра... знакомому.";
        link.l1.go = "rome_3";
        break;

    case "rome_3":
        AddQuestRecordInfo("Rome", "1");
        dialog.text = "В вашей просьбе нет ничего странного или зазорного, капитан. Знать изречения древних, вошедшие в историю - значит, быть образованным человеком. Вот, возьмите этот рукописный текст. Здесь то, что вы просили.";
        link.l1 = "Спасибо, Джино! Ты просто выручил меня! Займусь на досуге изучением...";
        link.l1.go = "exit";
        npchar.quest.rome = true;
        NextDiag.TempNode = "First time";
        break;

    case "chemistry":
        RemoveItems(pchar, "chemistry", 1);
        Log_Info("Вы отдали учебник химии Лавуазье");
        dialog.text = "Покажите... (смотрит) Уму непостижимо! 'Небольшой подарок', вы говорите?! Да этой книге цены нет! Где вы её достали?! Это же... настоящее сокровище!";
        link.l1 = "Я очень рад, что она тебе пригодится.";
        link.l1.go = "chemistry_1";
        break;

    case "chemistry_1":
        dialog.text = "(листает) Невероятно! А вот об этом я даже и не слышал... а это? А вот тут я ничего не понимаю... но разберусь, чёрт побери! Ох, и закипит же скоро работа в моей лаборатории! " + pchar.name + ", вы даже не осознаёте, ЧТО вы мне подарили...";
        link.l1 = "Почему не осознаю? Осознаю. Учёную книгу для учёного мужа...";
        link.l1.go = "chemistry_2";
        break;

    case "chemistry_2":
        dialog.text = "Но кто же автор этого чуда? Антуан Лоран Лавуазье, Франция... Никогда не слышал о таком. Но позвольте! Как же так! Год издания - 1789 год? Но ведь...";
        link.l1 = "Я тоже не знаю, почему на ней стоит этот год. И тебе задумываться над этим не советую. Если книга толковая - то что ещё нужно?";
        link.l1.go = "chemistry_3";
        break;

    case "chemistry_3":
        dialog.text = "Книга очень толковая, а с годом наверное опечатались... Неважно. Спасибо большое, капитан!";
        link.l1 = "Пожалуйста, Джино. Изучай на здоровье.";
        link.l1.go = "exit";
        if (CheckCharacterItem(pchar, "pistol7"))
        {
            link.l1 = "Это не всё, Джино. Я хочу показать тебе вот этот пистолет. Видел ли ты когда-нибудь что-то подобное?";
            link.l1.go = "colt";
        }
        npchar.quest.colt = true;
        break;

    case "colt":
        dialog.text = "Я не оружейник, но всё же взгляну... нет, никогда с таким не сталкивался. А что?";
        link.l1 = "Этот пистоль очень мощный и убойный, но к нему нужны специальные заряды. Ничего другого к нему не подходит. А как изготовить такие патроны - я понятия не имею. Вот я и пришёл к тебе за советом.";
        link.l1.go = "colt_1";
        break;

    case "colt_1":
        dialog.text = "У вас есть хоть один такой патрон показать мне для образца? Если нет, ничем помочь не смогу, я не представляю, что в него нужно засовывать.";
        if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
        {
            link.l1 = "Есть. Заряд состоит из двух частей: самого патрона с пулей и вот этой штуковины, без которой порох не взрывается.";
            link.l1.go = "colt_2";
        }
        else
        {
            link.l1 = "Вот незадача! Эх, досада-то какая! Ладно, может, отыщу, тогда и принесу.";
            link.l1.go = "exit";
            npchar.quest.sample = true;
        }
        DeleteAttribute(npchar, "quest.colt");
        break;

    case "colt_2":
        RemoveItems(pchar, "pistol7", 1);
        RemoveItems(pchar, "GunCap_colt", 1);
        RemoveItems(pchar, "shotgun_cartridge", 1);
        Log_Info("Вы отдали револьверный картридж");
        Log_Info("Вы отдали капсюль");
        PlaySound("interface\important_item.wav");
        dialog.text = "Очень интересно! Тут всё понятно, внутри находится порох, сверху - пуля, правда, какая-то необычная. А вот с этой 'штуковиной'... хм. Без него порох не взрывается, говорите? Занятно... Вот что, капитан, оставьте мне всё это для изучения - и пистолет, и заряды, и приходите через месяц, чтобы я спокойно смог разобраться.";
        link.l1 = "Договорились! Постарайся понять, что к чему, уж очень хочется пострелять из этого пистоля.";
        link.l1.go = "colt_3";
        break;

    case "colt_3":
        dialog.text = "Главная проблема - узнать, из чего состоит вещество, использующееся для взрыва пороха. Очень пригодится ваша книга, которую вы подарили. Я постараюсь.";
        link.l1 = "Хорошо. До встречи, Джино!";
        link.l1.go = "colt_4";
        break;

    case "colt_4":
        DialogExit();
        DeleteAttribute(npchar, "quest.sample");
        SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
        break;

    case "cartridge":
        dialog.text = "Да, я разобрался с зарядами к вашему пистолю. Надо отдать должное вашей подаренной книге - без неё у меня бы ничего не вышло. Но должен сразу предупредить, капитан: изготовление патронов и капсюлей к вашему оружию - дело непростое.";
        link.l1 = "Капсюлей?";
        link.l1.go = "cartridge_1";
        break;

    case "cartridge_1":
        dialog.text = "Это та самая 'штуковина', как вы выразились, которая подрывает порох в патроне. Но давайте всё по порядку. Вы готовы?";
        link.l1 = "Да! Я внимательно тебя слушаю.";
        link.l1.go = "cartridge_2";
        break;

    case "cartridge_2":
        AddQuestRecordInfo("Recipe", "shotgun_bullet");
        SetAlchemyRecipeKnown("shotgun_bullet");
        dialog.text = "Итак, для самого патрона вам надо отлить специальную пулю. Другая для данного пистоля не годится. Она должна быть особой конической формы. Для этого вам потребуется найти матрицу для таких пуль - пулелейку, как я её назвал. Берёте обычные свинцовые пули, расплавляете их в тигле на огне, затем жидкий свинец вливаете в форму, остужаете и извлекаете готовую пулю.";
        link.l1 = "И где мне взять эту пулелейку?";
        link.l1.go = "cartridge_3";
        break;

    case "cartridge_3":
        dialog.text = "Не знаю, капитан. Я всё-таки алхимик, а не кузнец. Возьмите за образец пулю из патрона, который вы мне дали. Может, что и придумаете.";
        link.l1 = "Ладно. Продолжаем...";
        link.l1.go = "cartridge_4";
        break;

    case "cartridge_4":
        AddQuestRecordInfo("Recipe", "shotgun_cartridge");
        SetAlchemyRecipeKnown("shotgun_cartridge");
        dialog.text = "Далее вам нужно изготовить вместилище для пороха, куда будете вставлять пулю. Подробную инструкцию я для вас написал - думаю, следуя моим советам, у вас всё получится. Изучите внимательно и пробуйте.";
        link.l1 = "Хорошо...";
        link.l1.go = "cartridge_5";
        break;

    case "cartridge_5":
        AddQuestRecordInfo("Recipe", "GunCap_colt");
        SetAlchemyRecipeKnown("GunCap_colt");
        dialog.text = "Теперь капсюли. Для заготовки потребуется очень тонкий медный лист - вы должны сами изготовить его из меди. Из листа вырезаются кружки по диаметру патрона, в них при помощи размягчённого воска помещается гремучее серебро.";
        link.l1 = "Гремучее серебро? А что это такое?";
        link.l1.go = "cartridge_6";
        break;

    case "cartridge_6":
        dialog.text = "Я тоже о таком не знал - вычитал секрет изготовления из вашей книги. Это белый порошок, получающийся из серебра, азотной кислоты и спирта. Взрывается при ударе и трении, поэтому и послужит для воспламенения пороха в патроне для вашего пистолета. Неприятная штука, он дважды взрывался у меня во время опытов, пока я разработал точный рецепт приготовления.";
        link.l1 = "Вот как хорошо, что у меня оказалась эта книга!";
        link.l1.go = "cartridge_7";
        break;

    case "cartridge_7":
        dialog.text = "Будьте крайне аккуратны: это взрывчатое вещество! Я мог бы и сам вам приготовить какое-то количество, но хранить гремучее серебро опасно: нужно сразу после изготовления поместить в капсюль и более не трогать. А медные капсюли я изготовить сам не могу - кузнечному делу не обучен.";
        link.l1 = "Хорошо. Давай рецепт, буду сам учиться.";
        link.l1.go = "cartridge_8";
        break;

    case "cartridge_8":
        AddQuestRecordInfo("Recipe", "OxyHydSilver");
        SetAlchemyRecipeKnown("OxyHydSilver");
        dialog.text = "Пожалуйста. Строго следуйте рецептуре и соблюдайте правильность процесса, иначе взлетите на воздух вместе со своими колбами.";
        link.l1 = "Я буду крайне осторожным.";
        link.l1.go = "cartridge_9";
        break;

    case "cartridge_9":
        dialog.text = "Также возьмите две склянки: вот эта - с азотной кислотой, а вот эта - со спиртом. Из этого количества вы сможете получить гремучего серебра на 20 капсюлей.";
        link.l1 = "Спасибо, Джино!";
        link.l1.go = "cartridge_10";
        break;

    case "cartridge_10":
        GiveItem2Character(pchar, "Mineral29");
        GiveItem2Character(pchar, "Mineral28");
        Log_Info("Вы получили склянку с азотной кислотой");
        Log_Info("Вы получили склянку со спиртом");
        PlaySound("interface\important_item.wav");
        dialog.text = "Также заберите ваш пистолет и образцовый патрон. Удачи, капитан, в изготовлении зарядов. Надеюсь, вы останетесь целы и невредимы.";
        link.l1 = "Я приму для этого все возможные меры. И, Джино: я не говорил тебе, что ты - гений?";
        link.l1.go = "cartridge_11";
        break;

    case "cartridge_11":
        TakeNItems(pchar, "pistol7", 1);
        TakeNItems(pchar, "shotgun_cartridge", 3);
        TakeNItems(pchar, "GunCap_colt", 1);
        dialog.text = "Вы вгоняете меня в краску, капитан, право...";
        link.l1 = "Ладно. Пока, Джино! Ты самый лучший алхимик!";
        link.l1.go = "cartridge_12";
        break;

    case "cartridge_12":
        DialogExit();
        DeleteAttribute(npchar, "quest.cartridge");
        break;

    // Addon 2016-1 Jason Пиратская линейка
    case "mtraxx":
        dialog.text = "Горд, горд... Можете ещё что-то сообщить об этом капитане? Откуда он, какой национальности?";
        link.l1 = "Нацию его не знаю, а родом он откуда-то с севера Европы... викингом его ещё называли иногда.";
        link.l1.go = "mtraxx_1";
        break;

    case "mtraxx_1":
        dialog.text = "Викинг! Да-да, я вспомнил, я читал об этом в одном историческом трактате. Горд - это укрепленный посёлок свободного ярла.";
        link.l1 = "Свободного ярла? Кто это?";
        link.l1.go = "mtraxx_2";
        break;

    case "mtraxx_2":
        dialog.text = "Это вроде князя у норманнов, жителей севера. Свободные ярлы с дружиной - викингами, отправлялись на кораблях, драккарах, в путешествия, точнее - набеги. Грабили, разбойничали, захватывали рабов... пираты, короче. А горды - это посёлки викингов, где они отдыхали, где жили их семьи, где они занимались хозяйством. Но это было давно, около шести веков назад. Потом свободных ярлов вместе с их дружинами изгнал свой же собственный народ - бондэры, или земледельцы, которым ярлы были как кость в горле.";
        link.l1 = "Всё ясно. Значит, горд - это его сухопутная база... Спасибо, Джино!";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
        break;

        // ----------------------------------------- Португалец ----------------------------------------------------
    case "Portugal":
        dialog.text = "Лихорадка и бред, говорите – это любопытно. Немедленно везите его на берег! Я посмотрю, что можно сделать. Но ничего не могу обещать, если состояние слишком запущенное... Он ваш офицер?";
        link.l1 = "Нет, слава Богу, не мой. Джино, послушай, не спрашивай кто он, просто сделай всё что возможно, это очень, очень важно!";
        link.l1.go = "Portugal_1";
        break;

    case "Portugal_1":
        dialog.text = "Хорошо, доставьте его в дом, в вашу комнату. Я пока подготовлю кое-какие микстуры... возможно, сможет помочь корень...";
        link.l1 = "Я сейчас же распоряжусь его доставить!";
        link.l1.go = "Portugal_2";
        break;

    case "Portugal_2":
        DialogExit();
        pchar.questTemp.Portugal = "Portugal_wait";
        int iShipType = GetCharacterShipType(pchar);
        ref rShip = GetRealShip(iShipType);
        sTemp = "My_" + rShip.CabinType;
        sld = characterFromId("PortugalDoctor");
        sld.dialog.currentnode = "Portugal_doctor_9";
        ChangeCharacterAddressGroup(sld, sTemp, "rld", "aloc0");
        LAi_SetStayType(sld);
        break;

    case "Portugal_nomoney":
        dialog.text = "Тогда постарайтесь их побыстрее найти - без лекарств я не смогу поставить больного на ноги, а если затянуть - будет уже поздно.";
        link.l1 = "Хорошо, я разыщу деньги.";
        link.l1.go = "exit";
        pchar.questTemp.Portugal.Nomoney = "true";
        break;

    case "Portugal_3":
        AddMoneyToCharacter(pchar, -5000);
        dialog.text = "Отлично, капитан. Теперь я займусь приготовлением нужных лекарств, а вам лучше оставить больного. Заходите завтра.";
        link.l1 = "Хорошо, Джино. Я верю в твои микстуры и в твоего гения.";
        link.l1.go = "exit";
        pchar.questTemp.Portugal = "TreatmentCurrent";
        pchar.GenQuest.CannotWait = true; //запрет ожидания
        break;

    case "Portugal_4":
        dialog.text = "Ну, думаю, ещё пару недель и он будет в полном порядке. Плясать, конечно, ещё не сможет, но на ногах стоять будет, это точно.";
        link.l1 = "Проклятье, у меня нет двух недель! Мне нужно.. отправляться как можно скорее!";
        link.l1.go = "Portugal_5";
        break;

    case "Portugal_5":
        dialog.text = "Капитан, я не волшебник, и говорю вам – этот человек всё ещё слишком слаб, и, иногда приступы возвращаются. Я не уверен, что он протянет и несколько дней на корабле – его нельзя перемещать!";
        link.l1 = "Хорошо-хорошо, но две недели, даже неделя, это слишком много!";
        link.l1.go = "Portugal_6";
        break;

    case "Portugal_6":
        dialog.text = "Три дня... да, думаю, через три дня, можете попробовать отплыть, но больному тогда потребуется постоянный присмотр, лекарства, и, вам придётся делать остановки.";
        link.l1 = "У меня есть доктор, который за ним приглядит. Через три дня, я вернусь, и мы его заберём – это самое большее, что я могу себе позволить. Лучше с остановками, но двигаться... да, и, ещё одно: Джино – ты гений!";
        link.l1.go = "Portugal_7";
        break;

    case "Portugal_7":
        dialog.text = "Спасибо, капитан. Приходите через три дня за своим другом, а пока не тревожьте его - ему нужен полный покой.";
        link.l1 = "Хорошо. Я всё понял. Заберу его через три дня.";
        link.l1.go = "Portugal_8";
        break;

    case "Portugal_8":
        DialogExit();
        SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
        pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
        pchar.quest.Portugal_Ill2.win_condition.l1.date.hour = sti(GetTime());
        pchar.quest.Portugal_Ill2.win_condition.l1.date.day = GetAddingDataDay(0, 0, 5);
        pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
        pchar.quest.Portugal_Ill2.win_condition.l1.date.year = GetAddingDataYear(0, 0, 5);
        pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver"; //чтобы не тянул
        pchar.questTemp.Portugal = "TreatmentComplete";
        pchar.quest.Avendel_room.win_condition.l1 = "location";
        pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
        pchar.quest.Avendel_room.function = "AvendelSpeach";
        break;

    case "Portugal_threedays":
        dialog.text = "Поправляется, но очень медленно. В путь отправиться он пока не может.";
        link.l1 = "Да-да, я помню, Джино. Три дня ещё не прошли...";
        link.l1.go = "exit";
        break;

    case "Portugal_9":
        pchar.quest.Portugal_Ill2.over = "yes";
        dialog.text = "Ухудшения нет, но и полегчало ему не слишком. Он все ещё не до конца в сознании – не понимает где он и зачем, впрочем, это его и не беспокоит, кажется, другое дело – приступы жара – они ещё продолжаются время от времени, я не уверен, что везти его сейчас такая хорошая идея.";
        link.l1 = "Я больше не могу ждать, итак мы пробыли тут слишком долго. Собирай микстуры, которыми его придется пичкать по дороге, и мы уходим. Надеюсь, этот негодяй достаточно крепок, и не умрёт раньше, чем его приговорят...";
        link.l1.go = "Portugal_10";
        break;

    case "Portugal_10":
        dialog.text = "Постойте, капитан! Я что - лечил приговоренного к смерти? Какого чёрта? Столько сил, а вы знаете, как сложно изготовить сушёный порошок...";
        link.l1 = "Джино, тебе не следовало этого знать. Не бери в голову – он пират, причем один из самых неприглядных представителей этого ремесла. Я должен доставить его на Кюрасао на свидание с властями Компании, как можно скорее, и точка.";
        link.l1.go = "Portugal_11";
        break;

    case "Portugal_11":
        dialog.text = "Хорошо, вам виднее. Пират, значит... на Кюрасао. Ладно, но скажу вам вот ещё что – первое время он будет всё больше спать, но корабельная качка и духота могут повернуть процесс вспять. Я рекомендую вам сделать остановку не позднее чем через несколько дней, и дать вашему... пленнику передохнуть на суше. Иначе – велик риск, что на Кюрасао его повесят посмертно...";
        link.l1 = "Хорошо, я так и сделаю. Мартиника будет в самый раз – почти середина пути. Надеюсь, ветер будет попутный – я забираю его, и мы уходим. Спасибо ещё раз, Джино.";
        link.l1.go = "Portugal_12";
        break;

    case "Portugal_12":
        dialog.text = "Не за что, капитан. Помните – четыре дня, ну пять, не больше. И еще одно... знаете, обычно, я спасаю жизни людям, не для того, чтобы их потом повесили. Врач в ответе за своих пациентов, какими бы они ни были. И мне крайне неприятно...";
        link.l1 = "Прости, что втянул в эту историю, но, без тебя у нас не было бы и шанса. А теперь, нам пора – иначе все ребята Португальца успеют собраться у парадных дверей встречать своего вожака.";
        link.l1.go = "Portugal_13";
        break;

    case "Portugal_13":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1); //Джино в свою комнату
        DeleteAttribute(pchar, "GenQuest.CannotWait");                                                                         //можно мотать время
        pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
        pchar.quest.Portugal_Ill3.win_condition.l1.date.hour = sti(GetTime());
        pchar.quest.Portugal_Ill3.win_condition.l1.date.day = GetAddingDataDay(0, 0, 5);
        pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
        pchar.quest.Portugal_Ill3.win_condition.l1.date.year = GetAddingDataYear(0, 0, 5);
        pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver"; //5 дней до Мартиники
        pchar.questTemp.Portugal = "ToMartinique";
        pchar.quest.Avendel_room1.win_condition.l1 = "location";
        pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
        pchar.quest.Avendel_room1.function = "AvendelSpeach";
        pchar.quest.Portugal_street.win_condition.l1 = "location";
        pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
        pchar.quest.Portugal_street.function = "PortugalOnStreet";
        break;
    // <-- Португалец
    case "guardoftruth_0":
        dialog.text = "Очень интересно... И чем же вы можете мне помочь? Я не нуждаюсь в помощи и не просил её...";
        link.l1 = "И все же она тебе понадобится. Ты послушай, что я тебе скажу, а потом уже делай выводы.";
        link.l1.go = "guardoftruth";
        break;

    case "guardoftruth":
        dialog.text = "Внимательно вас слушаю.";
        link.l1 = "Я недавно был в Сантьяго... у отца Винсенто. Так вот, он ищет своего пропавшего секретаря по имени... Господи, да что ты так сильно побледнел, Джино!";
        link.l1.go = "guardoftruth_1";
        break;

    case "guardoftruth_1":
        dialog.text = "Вы... вы были у инквизитора? Он...";
        link.l1 = "Не волнуйся, Джино. Я ни за что не выдам тебя отцу Винсенто, хотя именно это он мне и поручил: найти тебя и доставить к нему. Мне нужно узнать от тебя кое-что касательно информации, полученной тобой и отцом Винсенто от некого индейца племени ица. О Тайясале, о сокровищах, о каком-то 'зле'.";
        link.l1.go = "guardoftruth_2";
        break;

    case "guardoftruth_2":
        dialog.text = "Вижу, вы хорошо осведомлены. Это отец Винсенто вам всё рассказал?";
        link.l1 = "Что-то - он, а что-то я узнал из третьих уст. Но мне гораздо важнее услышать всё от тебя - как секретарь, ты, вероятно, вёл протокол допроса?";
        link.l1.go = "guardoftruth_3";
        break;

    case "guardoftruth_3":
        dialog.text = "Видели бы вы, капитан, что он сделал с этим несчастным индейцем!.. У меня просто мороз по коже при одном воспоминании об этом допросе.";
        link.l1 = "И всё-таки давай поговорим об этом. Кто этот индеец? Как он попал в руки отцу Винсенто?";
        link.l1.go = "guardoftruth_4";
        break;

    case "guardoftruth_4":
        dialog.text = "Он был в отряде индейцев ица, вышедшем из Тайясаля на поиски Маски Кукулькана - артефакта бога индейцев майя. Отряд столкнулся с шайкой белых авантюристов, искателями кладов под командованием шотландца Арчибальда Колхауна. После стычки в живых остался только этот индеец, Ксатл Ча. При нём были три занятных предмета, к которым я вернусь позже\nКолхаун попытался выведать у пленника что-либо о сокровищах, но тот был нем, как рыба. Тогда шотландец отвёз индейца в Сантьяго отцу Винсенто, так как знал, что инквизитор очень интересуется всякими туземными тайнами и легендами, и обменял его на грамоту, разрешающую ему посещать испанские поселения сроком на год\nПотом отец Винсенто взялся за индейца, и уже в его руках бедняга заговорил. Он рассказал много, очень много интересного. Услышанное повергло в шок самого инквизитора.";
        link.l1 = "Да ну? Что же могло заставить трепетать Его Преосвященство?";
        link.l1.go = "guardoftruth_5";
        break;

    case "guardoftruth_5":
        dialog.text = "Я расскажу по порядку. В глубине джунглей Юкатана стоит старый город майя - Тайясаль. Сейчас его населяют индейцы ица, прямые потомки майя, и пытаются следовать традициям и культуре своих предков. Безусловно, индейцы недовольны творящимся на архипелаге - я имею в виду засилие белых и захват ими земель коренных народов\nОднако ни у одного индейского племени нет такого богатого наследия, как у майя. Ица, их потомки, гордятся своим прошлым и мечтают о возвращении славных времён. А вот теперь - самое интересное. Около четверти века тому назад белыми авантюристами, случайно оказавшимися у Тайясаля, была похищена дочь верховного жреца ица\nЭто стало последней каплей, и Канек - верховный жрец - впал в ярость. Он решил провести один из самых таинственных, жутких и опасных ритуалов майя - призвать на землю индейское божество, чтобы стереть с земли предков белых завоевателей...";
        link.l1 = "Гм... Видимо, об этом 'демоне' и говорил отец Винсенто. Но каким образом это индейское божество должно было расправиться с белыми поселенцами? Явиться в образе дракона и испепелить всех?";
        link.l1.go = "guardoftruth_6";
        break;

    case "guardoftruth_6":
        dialog.text = "О, " + pchar.name + ", оставьте эти сказки об огнедышащих чудищах старушкам, нянчащим детей! Хотя вы почти угадали, но всё намного сложнее и... серьезнее. Даже потоп не может ныне остановить экспансию европейцев в Новый Свет - на место одного погибшего явится десять других. Канеку нужно было уничтожить саму возможность прихода и укрепления белых на земле индейцев.";
        link.l1 = "Но как же он собирался это сделать, если вторжение УЖЕ произошло?";
        link.l1.go = "guardoftruth_7";
        break;

    case "guardoftruth_7":
        dialog.text = "Верно мыслите, капитан... Обряд Канека, кроме призвания в помощь высшего существа, также осуществлял создание пространственно-временной воронки.";
        link.l1 = "Что ты сейчас сказал? Какой ещё воронки?";
        link.l1.go = "guardoftruth_8";
        break;

    case "guardoftruth_8":
        dialog.text = "Майя - великие мудрецы, капитан... Канек нашёл описание обряда, способного управлять временем.";
        link.l1 = "Вот это да! Невероятно!";
        link.l1.go = "guardoftruth_9";
        break;

    case "guardoftruth_9":
        dialog.text = "Слушайте дальше. Конечная цель обряда - измененить прошлое так, чтобы сделать невозможным появление белых в Новом Свете. А для этого нужно отправить в прошлое некого человека, обладающего авторитетом, силой, способностью вершить судьбы, но самое главное - наделённого современными знаниями\nКак вы думаете, " + pchar.name + ", что было бы с Колумбом, если бы его каравеллы были встречены у берегов Эспаньолы индейским флотом из фрегатов и галеонов, которые отдали бы салют прибывшим из нынешних орудий, а аркебузам белых солдат противостояли бы не луки и копья, а мортиры и мушкеты?";
        link.l1 = "Думаю, Америку бы так и не открыли...";
        link.l1.go = "guardoftruth_10";
        break;

    case "guardoftruth_10":
        dialog.text = "Именно! А возможно, ещё и какой-нибудь индейский 'Колумб' открыл бы Европу...";
        link.l1 = "Интересно, и кого же Канек собрался отправить в прошлое? Какого-нибудь своего голопузого воина? Сомневаюсь, что он сумеет многому научить своих пращуров...";
        link.l1.go = "guardoftruth_11";
        break;

    case "guardoftruth_11":
        dialog.text = "Не смейтесь, капитан. Канек не зря провёл много лет в храмах майя, изучая их письмена. В прошлое должно отправится вызванное этим обрядом индейское божество, воплощённое в человеческом облике...";
        link.l1 = "Джино, что за чушь ты порешь? От кого-кого, но от тебя...";
        link.l1.go = "guardoftruth_12";
        break;

    case "guardoftruth_12":
        dialog.text = "Даже Сын Господа нашего, Спаситель, Иисус Христос, явился на землю в человеческом обличии и был рождён от женщины, Пресвятой Девы Марии...";
        link.l1 = "Господи, Джино... ты серьёзно?";
        link.l1.go = "guardoftruth_13";
        break;

    case "guardoftruth_13":
        dialog.text = "Более чем. Ксатл Ча рассказывал очень убедительно...";
        link.l1 = "Но что за божество решил призвать Канек?";
        link.l1.go = "guardoftruth_14";
        break;

    case "guardoftruth_14":
        dialog.text = "Обряд предусматривал вызов только одного высшего существа. Крылатый змей, Кетцалькоатль, Кукулькан...";
        if (CheckAttribute(pchar, "questTemp.Dolly"))
            link.l1 = "Кукулькан?! Я уже имел неосторожность близко познакомиться с его 'духом', живущим в статуях. Так вот оно что... продолжай!";
        else
            link.l1 = "Хм. Интересно. Я уже слышал это имя от отца Винсенто... продолжай!";
        link.l1.go = "guardoftruth_15";
        break;

    case "guardoftruth_15":
        dialog.text = "Канек решил призвать Кукулькана, поскольку ица обладали древним артефактом этого божества - Маской Кукулькана. Только тот, кто владеет Маской, сможет пройти через временной портал в Тайясаль многовековой давности, и только её обладатель будет признан индейцами майя воплощением Кукулькана на земле. Без этого артефакта древние майя примут любого пришельца за чужака и расправятся с ним на жертвенном алтаре\nЖрец провёл ритуал: призвал Кукулькана воплотиться в теле смертного на земле и создал пространственно-временную воронку. В момент ритуала эта воронка на мгновение открыла врата в разные места пространства и времени и затянула в нашу реальность некоторое количество людей из будущего\nЭто делалось для того, чтобы принести воплощению Кукулькана знания не только современности, но даже будущего, чтобы увеличить его силу. Правда, в Тайясаль эти жертвы почему-то не попали, а рассеялись неведомо где. В Тайясале на месте свершения ритуала образовался портал Кукулькана, через который тот, когда явится в Тайясаль, сможет отправиться в прошлое вместе со своими знаниями\nТакже на архипелаге появились порталы для захвата людей и доставки их в Тайясаль, как потенциальных источников знаний и опыта. Однако эти порталы не выполнили своего предназначения за четверть века ни разу: никто не был захвачен и перенесен в Тайясаль...";
        if (CheckAttribute(pchar, "questTemp.Dolly"))
        {
            link.l1 = "Конечно... Потому что эти порталы перекидывают захваченных ими людей по кругу друг к дружке... Невероятно!";
            link.l1.go = "guardoftruth_15a";
        }
        else
        {
            link.l1 = "Очень занятно...";
            link.l1.go = "guardoftruth_16";
        }
        break;

    case "guardoftruth_15a":
        dialog.text = "Вы что, видели эти порталы? Расскажите!";
        link.l1 = "Как-нибудь потом, Джино... Сейчас меня больше интересует твой рассказ. Продолжай!";
        link.l1.go = "guardoftruth_16";
        break;

    case "guardoftruth_16":
        dialog.text = "Всё, что я сейчас рассказал, известно и отцу Винсенто. Немудрено, что он забеспокоился. Ведь если Кукулькан, ныне воплощенный в человека, доберётся с накопленными знаниями до портала в Тайясале, то последствия будут печальны. Это фактически конец света для нас с вами\nИзменится прошлое - изменится и будущее. Наша реальность претерпит изменения, фактически - исчезнет, заменившись другой. Возможно, мы с вами даже и не родимся, капитан. Или в лучшем случае - появимся в других условиях. Так что как только Кукулькан окажется в прошлом - мы с вами перестанем существовать.";
        link.l1 = "А в ком воплощён Кукулькан?";
        link.l1.go = "guardoftruth_17";
        break;

    case "guardoftruth_17":
        dialog.text = "А кто же его знает. Он может быть в любом человеке, кто родился четверть века назад, когда был совершён обряд. В вас, например... шучу, шучу. Но для нас не всё потеряно. Во-первых, воплощение Кукулькана - обычный смертный, а значит он может заболеть, утонуть, погибнуть от шальной пули, и конец света не состоится\nА во-вторых, в прошлое невозможно отправиться без Маски Кукулькана, а её Канек надежно припрятал... похоже, даже слишком надежно. Быть может, и сам воплощенный Кукулькан не найдёт её.";
        link.l1 = "Ну-ка, давай поподробнее!";
        link.l1.go = "guardoftruth_18";
        break;

    case "guardoftruth_18":
        dialog.text = "Спустя какое-то время после обряда к Тайясалю проникла группа испанских конкистадоров и почти добралась до сокровищницы. Ица сумели остановить кастильцев, перебив их, а одного взяли в плен - гиганта ростом почти семь футов и огромной силы\nКанек, обеспокоенный, что Маской Кукулькана может завладеть чужак, выкрав её из сокровищницы, и тем самым помешать великому плану, решил защитить реликвию. Он придумал свой собственый ритуал, пользуясь знаниями майя. Для этого ритуала он взял вещи, которые, по его мнению, были наделены магией белых людей\nЭто была дага, принадлежавшая самому Кортесу, и корабельный компас. Кроме того, этой дагой из спины испанца-гиганта вырезали большой кусок кожи, а его самого принесли в жертву Кукулькану на алтаре. Вот эти предметы - дага, компас и кусок кожи, были задействованы в ворожбе\nПосле ритуала в море недалеко от Юкатана образовался новый остров, на котором теперь и находится Маска Кукулькана. Где он - никто не знает. А найти его можно только при помощи даги, компаса и куска кожи, совместив определенным способом. И кроме того, на все предметы сокровищницы наложилось заклятие: ни один из них не может покинуть пределы архипелага!\nПри попытке вывоза судно будет захвачено штормом и выброшено на тот самый дикий остров, Ксочитэм, где спрятана Маска. Умно, правда?";
        link.l1 = "Не спорю. Но откуда же этот Ксатл Ча так подробно был обо всём осведомлён? Что-то не верится, что Канек делился тайными знаниями с простыми воинами...";
        link.l1.go = "guardoftruth_19";
        break;

    case "guardoftruth_19":
        dialog.text = "Дело в том, что всё это ему поведал нынешний вождь ица, Уракан, сын Канека. Он и отправил Ксатл Ча с отрядом воинов, чтобы тот нашёл тайный остров и Маску Кукулькана. Для этого он дал ему Стража Истины - так называются в совокупности дага, компас и кожаная карта...";
        link.l1 = "Почему - карта? И зачем Уракану понадобилась Маска? Он решил сам отправится в прошлое?";
        link.l1.go = "guardoftruth_20";
        break;

    case "guardoftruth_20":
        dialog.text = "Карта - потому что после ритуала на куске кожи появились контуры архипелага, словно карта. А Маска Уракану понадобилась по простой причине: он, в отличие от своего отца, не хочет разрушать существующую реальность - похоже, она его весьма устраивает. Он не хочет приносить себя в жертву ради славного будущего народа майя\nВидимо, Уракан вознамерился уничтожить Маску, и тем самым сделать для Кукулькана путешествие в прошлое невозможным. Но Ксатл Ча захватил Колхаун, а дальше - вы знаете. Так что посланец Уракана так и не добрался до Ксочитэма.";
        link.l1 = "Значит, конец света можно предотвратить, если найти и уничтожить Маску Кукулькана? А где сейчас этот... Страж Истины?";
        link.l1.go = "guardoftruth_21";
        break;

    case "guardoftruth_21":
        dialog.text = "Дага 'Коготь вождя' и компас 'Стрела пути' остались у Колхауна, а кожаная карта 'Двух появлений' скорее всего лежит где-то в инквизиции. Колхаун заткнул ей пленнику рот, использовав как кляп. Он понятия не имел, что это за предметы.";
        link.l1 = "Как ты сейчас сказал? 'Коготь вождя'? Чёрт возьми, но эта дага у меня! Мне её отдал Фадей в уплату долга моему брату! Смотри!";
        link.l1.go = "guardoftruth_22";
        break;

    case "guardoftruth_22":
        dialog.text = "Поразительно... Это и впрямь она. Я помню её.";
        link.l1 = "Джино, скажи: что именно из твоего рассказа известно отцу Винсенто?";
        link.l1.go = "guardoftruth_23";
        break;

    case "guardoftruth_23":
        dialog.text = "Всё, кроме того, что касается Стража Истины. А также того, как его заставить работать, чтобы найти таинственный остров с Маской Кукулькана. Это Ксатл Ча рассказал мне с глазу на глаз, перед тем, как я дал ему микстуру, упокоившую его навеки. Я не мог смотреть на то, как он страдает, и помог ему избавиться от мучений. Он умер с улыбкой на лице\nКонечно, я не мог после этого оставаться в Сантьяго. Да и были у меня серьёзные опасения, что я стал слишком важным и опасным свидетелем для инквизитора, а отец Винсенто не церемонится в выборе средств\nВедь кроме всего прочего, Ксатл Ча рассказал и о сокровищнице ица в Тайясале.";
        link.l1 = "До этих сокровищ уже добрался один искатель приключений по имени Мигель Дичозо. Не слышал о таком?";
        link.l1.go = "guardoftruth_24";
        break;

    case "guardoftruth_24":
        dialog.text = "Нет. И где же сейчас Дичозо с этими сокровищами?";
        link.l1 = "А вот это я и сам хочу узнать. Я, собственно, и пришёл к нашему с тобой разговору, отправившись по следу индейского золота. Дичозо повёз эти сокровища в Европу, но канул в никуда вместе с ними.";
        link.l1.go = "guardoftruth_25";
        break;

    case "guardoftruth_25":
        dialog.text = "Я скажу вам, где сокровища и сам Дичозо.";
        link.l1 = "Джино, ты меня поражаешь. Откуда тебе известно?!";
        link.l1.go = "guardoftruth_26";
        break;

    case "guardoftruth_26":
        dialog.text = "Вы могли это и сами понять из моего рассказа, капитан. На сокровища Тайясаля наложено заклятие - ни один предмет не может покинуть архипелаг. Любой корабль...";
        link.l1 = "...будет захвачен штормом и выброшен на остров с Маской Кукулькана! Как же я сразу не догадался! Значит, достаточно найти этот... Ксочитэм, чтобы завладеть и сокровищами, и самой Маской!";
        link.l1.go = "guardoftruth_27";
        break;

    case "guardoftruth_27":
        dialog.text = "Вы решили спасти мир, капитан?";
        link.l1 = "Я решил найти своего блудного брата... Джино, как заставить Стража Истины показать, где находится остров? Ты сказал, что знаешь!";
        link.l1.go = "guardoftruth_28";
        break;

    case "guardoftruth_28":
        dialog.text = "Я только образно понял, как он работает. До тех пор, пока у меня не будут все компоненты Стража - я ничего не смогу сказать вам.";
        link.l1 = "Хм. Дага у нас уже есть. Осталось найти компас и карту. Компас - надо искать у Колхауна, а карту - у отца Винсенто в инквизиции...";
        link.l1.go = "guardoftruth_29";
        break;

    case "guardoftruth_29":
        dialog.text = "Вы собираетесь назад к инквизитору? Но как же вы доложите ему про...";
        link.l1 = "Надо убедить отца Винсенто, что ты умер, Джино. Тогда он прекратит преследования. Скажем, тебя хватил удар при моем появлении. А в качестве доказательства ты мне дашь какую-нибудь вещь, которая знакома инквизитору.";
        link.l1.go = "guardoftruth_30";
        break;

    case "guardoftruth_30":
        dialog.text = "В версию 'удара' Винсенто не поверит, а вот в то, что я на ваших глазах выпил яд - будет правдоподобно. Расскажете инквизитору, что при упоминании его имени я схватил мензурку с прозрачной жидкостью и выпил её, после чего покраснел, посинел и упал на пол, задыхаясь, и через минуту отдал Богу душу\nСкажете, что при этом в комнате стоял запах миндаля - отец Винсенто сразу поймёт, что это за яд. А отдадите ему вот этот альманах - мои записи различных исследований, я никогда с ним не расставался.";
        link.l1 = "Замечательно. Потому как я намерен поддерживать контакт с инквизитором. Он наверняка знает многое, что касается нашего дела.";
        link.l1.go = "guardoftruth_31";
        break;

    case "guardoftruth_31":
        dialog.text = "Будьте острожны с отцом Винсенто. Он опасен, как тигр, и ведёт свою игру. Делиться с вами он не станет - ни сокровищами, ни славой.";
        link.l1 = "Я понимаю. Ладно, Джино, давай свой альманах и постарайся вспомнить, что тебе говорил индеец по поводу Стража Истины, ибо я намерен собрать его полностью. Я должен найти Ксочитэм, ибо уверен, что там отыщутся не только сокровища и артефакт майя, но и мой дорогой братец.";
        link.l1.go = "guardoftruth_32";
        break;

    case "guardoftruth_32":
        dialog.text = "Держите. Удачи вам, капитан!";
        link.l1 = "Я не прощаюсь, Джино...";
        link.l1.go = "guardoftruth_33";
        break;

    case "guardoftruth_33":
        DialogExit();
        Log_Info("Вы получили альманах");
        PlaySound("interface\important_item.wav");
        GiveItem2Character(pchar, "Almanac");
        ChangeItemDescribe("Almanac", "itmdescr_jinobook");
        pchar.questTemp.Guardoftruth = "twoitems";
        AddQuestRecord("Guardoftruth", "37");
        break;

    case "guardoftruth_34":
        dialog.text = "Это было трудно, капитан?";
        link.l1 = "Давай не будем об этом... Уж больно много было желающих завладеть этими вещами. Видать, не мне одному не дает покоя таинственный Ксочитэм.";
        link.l1.go = "guardoftruth_35";
        break;

    case "guardoftruth_35":
        dialog.text = "Могу себе представить... Кстати, как отец Винсенто? Вы поддерживаете с ним связь?";
        link.l1 = "Пока да, но, думаю, дальнейшее сотрудничество уже ни к чему. Компоненты Стража Истины у меня, а, значит, и ключ к местонахождению Ксочитэма. Что-то мне не хочется осведомлять Его Преосвященство о моих успехах.";
        link.l1.go = "guardoftruth_36";
        break;

    case "guardoftruth_36":
        dialog.text = "Будьте осторожны, " + pchar.name + ". У отца Винсенто сотни глаз и сотни рук. Длинных рук...";
        link.l1 = "Я за последнее время пережил столько, что теперь точно не боюсь ни отца Винсенто, ни его ищеек, ни его наймитов. Ладно. Пора бы нам с тобой заняться поиском Ксочитэма при помощи компонентов Стража. Ты знаешь, как это сделать?";
        link.l1.go = "guardoftruth_37";
        break;

    case "guardoftruth_37":
        dialog.text = "Не совсем. Слова Ксатл Ча были довольно расплывчатыми. Сдается мне, что индеец и сам толком не знал, как заставить Стража работать. Оставьте мне компоненты, а я поломаю голову над решением этой задачи. Зайдите ко мне через два дня - возможно, я разгадаю тайну.";
        link.l1 = "Хорошо, Джино. Буду надеяться на тебя. Вот, возьми: дага, карта и компас.";
        link.l1.go = "guardoftruth_38";
        break;

    case "guardoftruth_38":
        dialog.text = "Можете быть уверены - они останутся в целости и сохранности.";
        link.l1 = "Не сомневаюсь. Ну а теперь не буду тебе мешать, Джино. Удачных поисков!";
        link.l1.go = "guardoftruth_39";
        break;

    case "guardoftruth_39":
        DialogExit();
        NextDiag.CurrentNode = "First time";
        RemoveItems(pchar, "knife_01", 1);
        RemoveItems(pchar, "skinmap", 1);
        RemoveItems(pchar, "arrowway", 1);
        pchar.questTemp.Guardoftruth = "end";
        SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
        CloseQuestHeader("Guardoftruth");
        AddQuestRecord("Ksochitam", "1");
        break;

    case "ksochitam":
        dialog.text = "Частично. То есть, что-то есть, но как это привязать к жизненным реалиям - я пока не совсем понимаю. Давайте попробуем разобраться вместе.";
        link.l1 = "Давай! Рассказывай, какие у тебя догадки?";
        link.l1.go = "ksochitam_1";
        break;

    case "ksochitam_1":
        dialog.text = "Индеец, Ксатл Ча, по поводу Стража Истины сказал следующее: 'Коготь вождя заставит карту открыться. Стрела пути укажет нужное направление из каждого проявления'.";
        link.l1 = "И что тебе удалось сделать?";
        link.l1.go = "ksochitam_2";
        break;

    case "ksochitam_2":
        dialog.text = "Я догадался, как заставить 'карту открыться'. Вы смотрели карту Двух Появлений?";
        link.l1 = "Хм. А что там такого? Невнятные контуры архипелага.";
        link.l1.go = "ksochitam_3";
        break;

    case "ksochitam_3":
        GiveItem2Character(pchar, "skinmap");
        dialog.text = "Возьмите её и посмотрите ещё раз, внимательно.";
        link.l1 = "Ну, давай посмотрим, раз ты так настаиваешь.";
        link.l1.go = "ksochitam_4";
        break;

    case "ksochitam_4":
        DialogExit();
        NextDiag.CurrentNode = "ksochitam_wait";
        pchar.questTemp.Ksochitam = "skinmap_1";
        chrDisableReloadToLocation = true; //закрыть локацию
        break;

    case "ksochitam_wait":
        dialog.text = "Вы не посмотрели карту, " + pchar.name + "...";
        link.l1 = "Да-да, сейчас гляну...";
        link.l1.go = "exit";
        NextDiag.TempNode = "ksochitam_wait";
        break;

    case "ksochitam_5":
        dialog.text = "";
        link.l1 = "Посмотрел. И ничего нового не увидел: нечёткие очертания островов и Мэйна. А что там должно быть?";
        link.l1.go = "ksochitam_6";
        break;

    case "ksochitam_6":
        dialog.text = "Погодите. Теперь вы должны заставить карту открыться. Для этого возьмите дагу Коготь вождя и легонько проведите острием по карте. Только несильно, чтобы не повредить. Держите кинжал. И смотрите внимательно!";
        link.l1 = "Как интересно! Сейчас посмотрим...";
        link.l1.go = "ksochitam_7";
        break;

    case "ksochitam_7":
        DialogExit();
        GiveItem2Character(pchar, "knife_01");
        NextDiag.CurrentNode = "ksochitam_wait";
        pchar.questTemp.Ksochitam = "skinmap_2";
        sld = ItemsFromID("skinmap");
        sld.mark = 2;
        break;

    case "ksochitam_8":
        dialog.text = "Ну, заметили разницу?";
        link.l1 = "Да. Когда прикасаешься дагой к карте, на ней появляются две пометки, в виде черепов, причем всё время в одних и тех же местах...";
        link.l1.go = "ksochitam_9";
        break;

    case "ksochitam_9":
        dialog.text = "В одних и тех же ДВУХ местах, " + pchar.name + "! Вот почему её назвали картой Двух Появлений!";
        link.l1 = "И что это значит?";
        link.l1.go = "ksochitam_10";
        break;

    case "ksochitam_10":
        dialog.text = "Наверняка - многое... Вот только дальше начинаются лишь догадки. Эти черепа, как я понимаю, и есть 'проявления', о которых сказал Ксатл Ча. Значит, именно в них компас Стрела Пути укажет направление на Ксочитэм. Вы рассматривали этот компас, " + pchar.name + "?";
        link.l1 = "Да. На вид обычный корабельный компас, но вот ведёт себя, как ошалелый: стрелка всё время дёргается в разных направлениях, или вообще начинает вращаться с дикой скоростью.";
        link.l1.go = "ksochitam_11";
        break;

    case "ksochitam_11":
        dialog.text = "Я думал, что при установке компаса на карту в проявившиеся черепа стрелка компаса перестанет хаотически крутиться и укажет чёткое направление на карте. Для этого я, прикасаясь дагой к кожаной карте, установил компас сначала в одно проявление, потом во второе...";
        link.l1 = "И что?";
        link.l1.go = "ksochitam_12";
        break;

    case "ksochitam_12":
        dialog.text = "Безрезультатно. Компас не изменил своего поведения. Как крутилась стрелка, словно ненормальная, так и крутится. Видимо, я что-то делаю не так. Или неверно понимаю слова Ксатл Ча.";
        link.l1 = "Получается, дага и карта - работают, а компас - нет?";
        link.l1.go = "ksochitam_13";
        break;

    case "ksochitam_13":
        dialog.text = "Стрела пути наверняка тоже работает, просто мы не знаем, как его заставить это сделать. " + pchar.name + ", вы лучше меня разбираетесь в географии архипелага... Скажите, где находятся на Карибах места, обозначенные на карте Двух Появлений?";
        link.l1 = "Один момент! (смотрит)... Так-так... Проявление слева - это Западный Мэйн. Справа - похоже на остров Доминика. Вроде так.";
        link.l1.go = "ksochitam_14";
        break;

    case "ksochitam_14":
        dialog.text = "А вот теперь скажите: есть ли в этих краях что-нибудь такое... примечательное?";
        link.l1 = "В смысле?";
        link.l1.go = "ksochitam_15";
        break;

    case "ksochitam_15":
        dialog.text = "Да я и сам не знаю... Ну что-то особенное?";
        link.l1 = "Джино, перестань говорить загадками. Объясни популярно.";
        link.l1.go = "ksochitam_16";
        break;

    case "ksochitam_16":
        dialog.text = "Я могу предположить, что черепа на карте показывают некие места на реальной местности. Раз Стрела Пути не работает при установке её на карту в 'проявление', быть может, он заработает, оказавшись географически в месте, указанном 'проявлением' на карте?";
        link.l1 = "Джино, ты - гений! Но вот что это за места?.. Западный Мэйн, Доминика? Черепа очень большие, чтобы указать точно.";
        link.l1.go = "ksochitam_17";
        break;

    case "ksochitam_17":
        chrDisableReloadToLocation = false; //открыть локацию
        dialog.text = "" + pchar.name + ", давайте сделаем так: принесите бумажную карту архипелага, совместите её с картой Двух Появлений и отметьте на бумаге крестиками 'проявления'. Может, это натолкнёт вас на какое-то предположение?";
        if (CheckCharacterItem(pchar, "map_bad"))
        {
            link.l1 = "У меня есть вот эта потертая карта архипелага.";
            link.l1.go = "ksochitam_17_1";
        }
        if (CheckCharacterItem(pchar, "map_normal"))
        {
            link.l2 = "У меня есть вот эта весьма толковая карта архипелага.";
            link.l2.go = "ksochitam_17_2";
        }
        if (CheckCharacterItem(pchar, "Map_Best"))
        {
            link.l3 = "У меня есть вот эта отличная карта архипелага.";
            link.l3.go = "ksochitam_17_3";
        }
        link.l4 = "Договорились. Я принесу карту и мы продолжим...";
        link.l4.go = "ksochitam_17_4";
        break;

    case "ksochitam_17_1":
        dialog.text = "Ну же, " + pchar.name + "! Этот пергамент времён Колумба немногим информативнее кожаной карты. Я уверен, что есть что-то получше этого старья. Принесите другую карту, поновее!";
        link.l1 = "Хорошо...";
        link.l1.go = "exit";
        NextDiag.TempNode = "ksochitam_map_wait";
        break;

    case "ksochitam_17_2":
        dialog.text = "Превосходно! Теперь отметьте на этой карте места проявлений крестом. Так нам будет проще строить предположения.";
        link.l1 = "Сейчас сделаем, Джино!";
        link.l1.go = "ksochitam_18";
        break;

    case "ksochitam_17_3":
        dialog.text = "Жалко уродовать такую великолепную карту нашими пометками. Вам она ещё пригодится, " + pchar.name + ". Принесите другую карту, попроще!";
        link.l1 = "Хорошо...";
        link.l1.go = "exit";
        NextDiag.TempNode = "ksochitam_map_wait";
        break;

    case "ksochitam_17_4":
        DialogExit();
        NextDiag.CurrentNode = "ksochitam_map_wait";
        break;

    case "ksochitam_map_wait":
        dialog.text = "Вы принесли карту архипелага, " + pchar.name + "?";
        if (CheckCharacterItem(pchar, "map_bad"))
        {
            link.l1 = "У меня есть вот эта потертая карта архипелага.";
            link.l1.go = "ksochitam_17_1";
        }
        if (CheckCharacterItem(pchar, "map_normal"))
        {
            link.l2 = "У меня есть вот эта весьма толковая карта архипелага.";
            link.l2.go = "ksochitam_17_2";
        }
        if (CheckCharacterItem(pchar, "Map_Best"))
        {
            link.l3 = "У меня есть вот эта отличная карта архипелага.";
            link.l3.go = "ksochitam_17_3";
        }
        link.l4 = "Пока нет, но я уже договорился о покупке. Скоро карта будет у меня, и мы продолжим...";
        link.l4.go = "ksochitam_17_4";
        break;

    case "ksochitam_18":
        chrDisableReloadToLocation = true; //закрыть локацию
        DialogExit();
        NextDiag.CurrentNode = "ksochitam_19";
        LAi_SetActorType(pchar);
        LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
        break;

    case "ksochitam_19":
        dialog.text = "";
        link.l1 = "Готово... Пометки я сделал, но всё равно о точности говорить не приходится. Первое место получилось где-то на северо-запад от Блювельда, в джунглях, а второе - центр острова Доминика.";
        link.l1.go = "ksochitam_20";
        break;

    case "ksochitam_20":
        dialog.text = "У вас есть предположения, что это за места могут быть?";
        link.l1 = "Понятия не имею. Но думаю, что надо отправляться туда, держа в руках Стрелу Пути, и смотреть за его поведением. Это, конечно, поиски чёрной кошки в тёмной комнате, но других предположений у нас всё равно нет.";
        link.l1.go = "ksochitam_21";
        break;

    case "ksochitam_21":
        dialog.text = "Я согласен с вами, " + pchar.name + ". Позволите, я поплыву вместе с вами?";
        link.l1 = "Тебе интересно, верно ли твоё предположение? Я буду только рад, Джино, если ты ступишь на палубу моего корабля. Собирайся в путь!";
        link.l1.go = "ksochitam_22";
        break;

    case "ksochitam_22":
        dialog.text = "Это не займёт много времени. Я буду готов через несколько часов. Вот, возьмите вашу Стрелу Пути.";
        link.l1 = "Добро пожаловать на борт!";
        link.l1.go = "ksochitam_23";
        break;

    case "ksochitam_23":
        LAi_SetOwnerType(npchar);
        DialogExit();
        NextDiag.CurrentNode = "ksochitam_24";
        chrDisableReloadToLocation = false; //открыть локацию
        LAi_SetPlayerType(pchar);
        GiveItem2Character(pchar, "arrowway");
        pchar.questTemp.Ksochitam = "seekway";
        sld = ItemsFromID("skinmap");
        sld.mark = 1;
        pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
        pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
        pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
        AddQuestRecord("Ksochitam", "2");
        break;

    case "ksochitam_24":
        dialog.text = "Да-да, " + pchar.name + ", я уже собираюсь. Скоро буду готов.";
        link.l1 = "...";
        link.l1.go = "exit";
        NextDiag.TempNode = "ksochitam_24";
        break;

    case "ksochitam_25":
        dialog.text = "Ну что, " + pchar.name + ", как успехи в поисках?";
        link.l1 = "Наша догадка подтвердилась. Я нашел то, на что указывало 'проявление' на карте. Это индейский истукан в джунглях.";
        link.l1.go = "ksochitam_26";
        break;

    case "ksochitam_26":
        dialog.text = "О! Вероятно, это один из тех истуканов, призванных переносить людей в Тайясаль! Помните, я вам рассказывал? Ну, и что показал компас Стрела Пути?";
        link.l1 = "Он указал на северо-восток. Я отметил на карте направление. Однако нарисованная линия пересекает чуть ли не всё Карибское море. Чтобы найти Ксочитэм, надо отправляться ко второму 'проявлению', на Доминике.";
        link.l1.go = "ksochitam_27";
        break;

    case "ksochitam_27":
        dialog.text = "Уверен, это будет ещё один истукан... вы согласны с моей гипотезой, " + pchar.name + "?";
        link.l1 = "Вполне, Джино. А теперь не будем терять времени и отправимся на поиски.";
        link.l1.go = "ksochitam_28";
        break;

    case "ksochitam_28":
        DialogExit();
        locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
        break;

    case "ksochitam_29":
        dialog.text = "Ну что, " + pchar.name + ", удалось отыскать что-нибудь интересное?";
        link.l1 = "Да. Наша догадка подтвердилась. Я нашел то, на что указывало 'проявление' на карте. Это индейский истукан в джунглях.";
        link.l1.go = "ksochitam_30";
        break;

    case "ksochitam_30":
        dialog.text = "О! Вероятно, это один из тех истуканов, призванных переносить людей в Тайясаль! Помните, я вам рассказывал? Ну, и что показал компас Стрела Пути?";
        link.l1 = "Он указал на западо-северо-запад. Я отметил на карте направление. Однако нарисованная линия пересекает чуть ли не всё Карибское море. Чтобы найти Ксочитэм, надо отправляться ко второму 'проявлению', на Мэйне.";
        link.l1.go = "ksochitam_27";
        break;

    case "ksochitam_31":
        dialog.text = "Ну как, " + pchar.name + ", отыскали второго истукана?";
        link.l1 = "Да. Отыскал и начертил на карте направление, указанное Стрелой Пути. Теперь мы знаем местоположение Ксочитэма, пусть и не идеально точное, но знаем! Я обыщу весь район в месте, где пересеклись линии, но найду этот чертов остров!";
        link.l1.go = "ksochitam_32";
        break;

    case "ksochitam_32":
        dialog.text = "Рад слышать столько энтузиазма в вашем голосе. Однако имеет смысл хорошенько подготовиться к предстоящей экспедиции - неизвестно, что нас ждёт на этом острове. Что-то я сомневаюсь, что мы там встретим радушный приём...";
        link.l1 = "Ты опасаешься чего-то конкретного, или просто высказываешь беспокойство?";
        link.l1.go = "ksochitam_33";
        break;

    case "ksochitam_33":
        dialog.text = "Подумайте сами, " + pchar.name + ". Ксочитэм возник в результате применения Канеком магии индейцев майя. Это неестественное образование, и к тому же обладающее злой и разрушительной силой. Неизвестно, что ожидает нас там, но навряд ли это будет ясное солнышко, ласковое море и тихий ветерок.";
        link.l1 = "Хорошо, Джино. Я учту твои слова и как следует подготовлюсь перед походом: снаряжу корабль, запасусь зельями и боеприпасами...";
        link.l1.go = "ksochitam_34";
        break;

    case "ksochitam_34":
        dialog.text = "Это очень разумное решение. Ну что же, а теперь - на корабль?";
        link.l1 = "Точно! И - в путь!";
        link.l1.go = "ksochitam_28";
        break;

    case "ksochitam_35":
        dialog.text = "Прибыли, " + pchar.name + "! Ух, какой ветер завывает!";
        link.l1 = "Да, Джино, ты был прав насчёт того, что нас тут не ждёт ясное солнышко... Да и вообще неизвестно, что нас тут ждёт.";
        link.l1.go = "ksochitam_36";
        break;

    case "ksochitam_36":
        dialog.text = "Ну и выбрали же вы местечко для высадки, капитан! Сплошные скалы да утёсы! И как пробираться в глубь острова отсюда?";
        link.l1 = "Ни одной удобной бухты для высадки не видно на этом острове из-за шторма! Хоть эту нашли, и то ладно! А проход в этих утёсах как-нибудь найду, и не в таких переделках бывали. Так что не дрейфь, дружище!";
        link.l1.go = "ksochitam_37";
        break;

    case "ksochitam_37":
        dialog.text = "Не нравится мне этот остров, " + pchar.name + "! Какой-то он жуткий. И шторм этот, похоже, только вокруг этого кусочка суши и наблюдается. Определенно проклятое место!";
        link.l1 = "Мне тоже здесь не по себе, Джино. Но надо же что-то выяснить по поводу 'Санта-Квитерии' и маски Кукулькана! Раз остров существует - значит, история с Кукульканом вовсе не сказки, и нам всем угрожает гибель, если он доберется до Тайясаля с маской...";
        link.l1.go = "ksochitam_38";
        break;

    case "ksochitam_38":
        dialog.text = "Попытайтесь найти маску, капитан! Это важнее всех сокровищ мира вместе взятых! Она точно должна быть где-то здесь! Тогда мы разрушим планы Кукулькана - не позволим ему отправиться в прошлое!";
        link.l1 = "А как она выглядит эта маска - ты не знаешь?";
        link.l1.go = "ksochitam_39";
        break;

    case "ksochitam_39":
        dialog.text = "Понятия не имею! Но думаю, вы сразу узнаете её - это древний индейский артефакт, его трудно с чем-то перепутать!";
        link.l1 = "Понятно. Буду смотреть в оба! Ладно, Джино, возвращайся назад на корабль! Не стоит тебе разгуливать по этому острову - твоя голова слишком дорого стоит, чтобы ей рисковать!";
        link.l1.go = "ksochitam_40";
        break;

    case "ksochitam_40":
        dialog.text = "Не буду перечить, капитан: мне и в самом деле здесь жутко, да и боец из меня никудышный. И вдогонку совет: компоненты Стража Истины обладают некой магией, напрямую связанной с Ксочитэмом. Ксатл Ча упомянул, что дага Коготь вождя имеет власть над существами, населяющими этот остров. Что это конкретно означает - я не понял. Но может вы разберётесь\nЯ буду в кают-компании. Если у вас вдруг возникнет тупиковая ситуация - возвращайтесь на корабль и расскажите мне, может, я смогу дать совет.";
        link.l1 = "Хорошо. А теперь, Джино, пожелай мне удачи!";
        link.l1.go = "ksochitam_41";
        break;

    case "ksochitam_41":
        dialog.text = "Удачи, " + pchar.name + "! И да хранит вас Господь!";
        link.l1 = "...";
        link.l1.go = "ksochitam_42";
        break;

    case "ksochitam_42":
        DialogExit();
        NextDiag.CurrentNode = "adversary";
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "aloc0", "Ksochitam_JinoStay", 10.0);
        AddQuestRecord("Ksochitam", "6");
        break;

    case "adversary":
        dialog.text = "Как успехи, " + pchar.name + "? Требуется совет?";
        if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
        {
            link.l1 = "Этот проклятый остров буквально кишит нечистью, причём мерзкие скелеты на удивление крепкие орешки. Ума не приложу, как с ними воевать.";
            link.l1.go = "adversary_1";
        }
        if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
        {
            link.l1 = "Если от развилки пойти левее, то попадаешь в пещеру. А вот куда идти дальше? Боюсь, это тупик...";
            link.l1.go = "adversary_2";
        }
        if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
        {
            link.l1 = "Я нашёл проход в мокрой пещере - можно поднырнуть в её подводную часть. Но что-то я никак не могу найти оттуда никакого выхода...";
            link.l1.go = "adversary_3";
        }
        if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
        {
            link.l1 = "Если от развилки пойти левее, то попадаешь в пещеру. А вот куда идти дальше? Боюсь, это тупик...";
            link.l1.go = "adversary_4";
        }
        if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
        {
            link.l1 = "В большой пещере есть место, где можно нырнуть под воду и попасть в затопленную часть. Вот только похоже, что она никуда не ведёт...";
            link.l1.go = "adversary_5";
        }
        link.l10 = "Пока всё нормально, Джино, пытаюсь справиться сам.";
        link.l10.go = "exit";
        NextDiag.TempNode = "adversary";
        break;

    case "adversary_1":
        dialog.text = "Я как раз вспомнил слова Ксатл Ча про Коготь вождя. Попробуйте вооружиться ей в битве против скелетов - недаром индеец сказал, что эта дага имеет власть над обитателями Ксочитэма.";
        link.l1 = "Обязательно попробую!";
        link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
        break;

    case "adversary_2":
        dialog.text = "Как выглядит эта пещера?";
        link.l1 = "Ну, не очень большая полость в скале, мокрая, на дне вода колышется, словно от прибоя...";
        link.l1.go = "adversary_2_1";
        break;

    case "adversary_2_1":
        dialog.text = "Если вода колышется волнами - значит, пещера имеет связь с морем, и не может быть тупиковой. Ищите проход, он точно должен быть.";
        link.l1 = "Пойду искать...";
        link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
        break;

    case "adversary_3":
        dialog.text = "Если в затопленную пещеру можно пройти из основной, и в основной каверне вода колышется, как от прибоя - значит, подводная пещера обязательно имеет второй выход. Ищите получше, но будьте осторожны, не утоните!";
        link.l1 = "Пойду нырять...";
        link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
        break;

    case "adversary_4":
        dialog.text = "Как выглядит эта пещера?";
        link.l1 = "Ну, довольно большая, с несколькими кавернами, мокрая, есть озерцо со стоячей водой...";
        link.l1.go = "adversary_4_1";
        break;

    case "adversary_4_1":
        dialog.text = "Если вода стоячая - значит, пещера не имеет прямой связи с морем и вполне может быть тупиковой. Возможно, второго выхода в ней нет.";
        link.l1 = "Я тоже так подумал. Сколько ни искал - в нее всего один вход, он же выход...";
        link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
        break;

    case "adversary_5":
        dialog.text = "Если в основной пещере вода стоячая - то вполне возможно, что так оно и есть. Поищите ещё, но не огорчайтесь, если ничего не найдёте. Вполне вероятно, что пещера окажется тупиковой.";
        link.l1 = "Ясно...";
        link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
        break;

    case "adversary_6":
        dialog.text = "" + pchar.name + ", нас атакуют испанские корабли! Сейчас не лучшее время для бесед!";
        link.l1 = "Да, конечно...";
        link.l1.go = "exit";
        NextDiag.TempNode = "adversary_6";
        break;

    case "ksochitam_43":
        dialog.text = "Судя по вашим горящим глазам, вы нашли, что искали?";
        link.l1 = "Да. И сокровища Мигеля Дичозо, и маску Кукулькана. Теперь его воплощению никогда не изменить будущее!";
        link.l1.go = "ksochitam_44";
        break;

    case "ksochitam_44":
        dialog.text = "Невероятно! Вы герой, " + pchar.name + "...";
        link.l1 = "Джино, ты уверен, что для того, чтобы разрушить планы Кукулькана, достаточно не дать ему завладеть маской?";
        link.l1.go = "ksochitam_45";
        break;

    case "ksochitam_45":
        dialog.text = "Со слов Ксатл Ча - да. А он цитировал Уракана, сына Канека, который и вызвал Кукулькана. А у вас есть сомнения?";
        link.l1 = "В бухте меня встретил гость из прошлого - Алонсо де Мальдонадо. Он был в Тайясале, когда Канек проводил ритуал создания Стража Истины. Его затянуло в пространственно-временную воронку, таким образом он остался жив...";
        link.l1.go = "ksochitam_46";
        break;

    case "ksochitam_46":
        dialog.text = "";
        link.l1 = "Так вот, он утверждал, что для того, чтобы обезопасить наш мир полностью, нужно закрыть Кукулькану доступ в прошлое в принципе - закрыть портал. Для этого необходимо уничтожить маску на каком-то алтаре в Тайясале.";
        link.l1.go = "ksochitam_47";
        break;

    case "ksochitam_47":
        dialog.text = "И вы что, намерены отправиться в Тайясаль? Это безумие! " + pchar.name + ", у вас есть маска, без неё воплощение Кукулькана не сможет что-либо сделать! В этом был уверен сам Канек! И Уракан именно для этого отправил Ксатл Ча на поиск Ксочитэма - завладеть маской.";
        link.l1 = "А если этот Уракан планировал уничтожить маску в Тайясале?";
        link.l1.go = "ksochitam_48";
        break;

    case "ksochitam_48":
        dialog.text = "" + pchar.name + ", ещё ни один человек, кроме Дичозо, не вышел из Тайясаля живым. Ну, и Мальдонадо, но это исключение. Даже если воплощение Кукулькана перенесётся в прошлое, он будет убит древними майя!";
        link.l1 = "А если нет? А если они его не убьют и признают?";
        link.l1.go = "ksochitam_49";
        break;

    case "ksochitam_49":
        dialog.text = "Так вы намерены отправиться в Тайясаль?";
        link.l1 = "Не знаю, Джино. Я не знаю...";
        link.l1.go = "ksochitam_50";
        break;

    case "ksochitam_50":
        dialog.text = "Тогда подумайте хорошенько, стоит ли это делать. Своё мнение я высказал. Дальше решайте сами... " + pchar.name + ", вы отвезёте меня домой в Сент-Джонс?";
        link.l1 = "Конечно, Джино. Отправляемся в путь как можно скорее. Мне уже осточертел этот кошмарный остров.";
        link.l1.go = "ksochitam_51";
        break;

    case "ksochitam_51":
        DialogExit();
        NextDiag.CurrentNode = "ksochitam_52";
        bQuestDisableMapEnter = false; //открыть карту
        DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
        DeleteAttribute(pchar, "GenQuest.CannotWait"); //можно мотать время
        AddQuestRecord("Ksochitam", "16");
        pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
        pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
        pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
        pchar.questTemp.Ksochitam = "gohome";
        break;

    case "ksochitam_52":
        dialog.text = "Мы скоро будем дома, " + pchar.name + "? Я уже соскучился по своим колбам и пробиркам...";
        link.l1 = "Да-да, Джино, скоро мы прибудем на Антигуа.";
        link.l1.go = "exit";
        NextDiag.TempNode = "ksochitam_52";
        break;

    case "ksochitam_53":
        dialog.text = "Я рад, что мы наконец-то вернулись домой! Не представляю, как вы, моряки, столько времени проводите на кораблях...";
        link.l1 = "Дело привычки, Джино.";
        link.l1.go = "ksochitam_54";
        break;

    case "ksochitam_54":
        dialog.text = "С огромным удовольствием сейчас прилягу на кровать, которая стоит на твердой земле... Надеюсь, " + pchar.name + ", вы выбросили из головы мысли о походе на Тайясаль?";
        link.l1 = "Не знаю, Джино. Честно сказать - до сих пор терзают сомнения.";
        link.l1.go = "ksochitam_55";
        break;

    case "ksochitam_55":
        dialog.text = "Уничтожьте маску Кукулькана и живите спокойно, капитан. Хотите, мы прямо сейчас растворим её в самой сильной кислоте? Я не пожалею ради такого дела.";
        link.l1 = "Знаешь, я повременю с этим. Уничтожить всегда успеем.";
        link.l1.go = "ksochitam_56";
        break;

    case "ksochitam_56":
        dialog.text = "Как знаете. Если решите избавить мир от этого артефакта - обращайтесь... Спасибо за увлекательное путешествие, капитан!";
        link.l1 = "Не за что, Джино. Ещё увидимся!";
        link.l1.go = "exit";
        NextDiag.TempNode = "first time";
        AddDialogExitQuestFunction("Ksochitam_TripComplete");
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    //--> блок реагирования на попытку залезть в сундук
    case "Man_FackYou":
        dialog.text = LinkRandPhrase("Да ты " + GetSexPhrase("вор, милейший! Стража, держи его", "воровка! Стража, держи её") + "!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи " + GetSexPhrase("вора", "воровку") + "!!!", "Стража! Грабят!!! Держи " + GetSexPhrase("вора", "воровку") + "!!!");
        link.l1 = "А-ать, дьявол!!!";
        link.l1.go = "exit";
        LAi_group_Attack(NPChar, Pchar);
        break;
        //<-- блок реагирования на попытку залезть в сундук
    }
}