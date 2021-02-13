// Диалог начала игры (туториал) 03.10.06 boal
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    ref sld;

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "Finish_2":
        DoQuestFunctionDelay("Tut_locCamera_2", 0.1);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        LAi_RemoveCheckMinHP(Pchar); // снимем проверки
        LAi_SetImmortal(pchar, false);
        LAi_SetPlayerType(pchar);
        InterfaceStates.Buttons.Save.enable = true;
        DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
        break;

    case "ChangePIRATES":
        LAi_SetCitizenTypeNoGroup(NPChar);
        LAi_SetPlayerType(pchar);
        NextDiag.CurrentNode = "Node_5";
        DialogExit();
        pchar.SystemInfo.ChangePIRATES = true;
        LaunchCharacter(pchar);
        break;

    case "ChangePIRATES_Jess":
        LAi_SetCitizenTypeNoGroup(NPChar);
        LAi_SetPlayerType(pchar);
        NextDiag.CurrentNode = "Node_5_Jess";
        DialogExit();
        pchar.SystemInfo.ChangePIRATES = true;
        LaunchCharacter(pchar);
        break;

    case "Teach_battle_1":
        LAi_SetPlayerType(pchar);
        NextDiag.CurrentNode = "Teach_6";
        AddDialogExitQuestFunction("Tut_TeachBattle");
        DialogExit();
        break;

    case "First time":
        NextDiag.TempNode = "First time";
        EndQuestMovie();
        InterfaceStates.Buttons.Save.enable = false;
        LAi_LockFightMode(Pchar, false);
        LAi_SetActorTypeNoGroup(Pchar);
        LAi_ActorTurnToCharacter(Pchar, NPChar);
        if (pchar.name == "Джессика")
        {
            dialog.text = "Наконец-то вы снова на ногах, капитан. Хвала Всевышнему, а то мы уж и не знали, что думать.";
            if (bBettaTestMode)
            {
                link.l0 = "BetaTest - пропустить и начать игру";
                link.l0.go = "Finish_2";
            }
            link.l1 = "Сандро? Черт возьми, что произошло? И почему так адски болит голова?..";
            link.l1.go = "Node_1_Jess";
        }
        else
        {
            dialog.text = "Вот, капитан, теперь вы хоть на себя стали похожи. Как себя чувствуете?";
            if (bBettaTestMode)
            {
                link.l0 = "BetaTest - пропустить и начать игру";
                link.l0.go = "Finish_2";
            }
            link.l1 = "Хм... а раньше на кого был" + GetSexPhrase("", "а") + " похож" + GetSexPhrase("", "а") + "?";
            link.l1.go = "Node_1";
        }
        break;

    case "Node_1":
        dialog.text = "Да на безбожников этих краснорожих, даже на их языке говорили.";
        link.l1 = "Дьявол! Сандро, что ты несешь?!";
        link.l1.go = "Node_2";
        break;

    case "Node_1_Jess":
        dialog.text = "Так вы ничего не помните? Да и немудрено, другой бы от такой контузии давно загнулся, или всю оставшуюся жизнь улыбался и штаны пачкал, а вы оказались крепким орешком. Правда, ослабли очень, еле на ногах держитесь - скоро уж полгода как пытаемся вас выходить.";
        link.l1 = "Расскажи толком, что за контузия - видишь, не помню ничего.";
        link.l1.go = "Node_2_Jess";
        break;

    case "Node_2":
        dialog.text = "Да вы не волнуйтесь, нельзя вам волноваться. Вы воздухом подышите, на море посмотрите, вот голова и прояснится. Доктор так и говорил, - если в себя придет - ничего помнить не будет, - вот вы и не помните, и незачем вам.";
        link.l1 = "Интересное дело - а, если не придет?";
        link.l1.go = "Node_3";
        break;

    case "Node_2_Jess":
        dialog.text = "Эх, да что здесь рассказывать... Говорили мы вам - и я, и старпом, - бросайте вы этого Белтропа, доведёт он нас до цугундера. Нет же!.. Вот и доигрались, пока этот тип в маске не послал вам пулю в затылок! Да благодарите Господа и свою пышную шевелюру, что пуля краем прошла. Только кость раздробила, а в черепе не застряла, иначе не жить бы вам\nЧто крови много было, и сознание потеряли - это даже хорошо - Маска решил, что с вами все кончено. Пока он кинулся, мы уже успели вытащить вас из развалин той старой церкви.";
        link.l1 = "Проклятье! Маска пытался меня убить... Никому нельзя верить... А что с Лоуренсом? Он жив?";
        link.l1.go = "Node_3_Jess";
        break;

    case "Node_3":
        dialog.text = "А, если не придет, говорит, то все, везите в приют для душевнобольных и даже не сумлевайтесь. Ибо не он это уже - раздвоение личное... А мы с Хопкинсом думаем - как же не он" + GetSexPhrase("", "а") + ", ежели он" + GetSexPhrase("", "а") + "! Только, вроде, с похмелья сильного, и все браниться норовит, а язык заплетается, и речь на манер туземцев выходит. Почитай, полгода так с вами и пронянькались, в конце уже и понимать приноровились. Только оружие убрали от греха подальше, и доктор рому не велел давать...";
        link.l1 = "Что за чушь ты несёшь - неужели всё это со мной было?";
        link.l1.go = "Node_4";
        break;

    case "Node_3_Jess":
        dialog.text = "Нет, слава Богу. Ой, извините... Вздёрнули его, Маска приказал повесить. А самого Маску, поговаривают, Акула зарезал. А по мне - так туда им обоим и дорога. Оба одним миром мазаны - негодяи. Столько крови вам попортили, мерзавцы!";
        link.l1 = "Нехорошо так о покойных... Да и былого уже не воротишь. Бог им судья... Спасибо вам, братцы, что из могилы вытащили, я этого не забуду.";
        link.l1.go = "Node_4_Jess";
        break;

    case "Node_4":
        dialog.text = "Вот вам крест. Мы и сами испугались - а ну как в себя не придете, что делать будем? И чем только эти голодранцы краснозадые вас опоили, проклятые! Ну, - слава Богу, - вы уже оклемались. Сейчас-то как себя чувствуете?";
        link.l1 = "Опоили, говоришь... очень на то похоже - не помню ничегошеньки... Дай-ка я с мыслями соберусь, да в себя приду. (создание своего типа героя).";
        link.l1.go = "ChangePIRATES";
        link.l2 = "Да вроде нормально себя чувствую. Только голова чуть кружится, будто с похмелья...";
        link.l2.go = "Node_5";
        break;

    case "Node_4_Jess":
        dialog.text = "Это наш долг, капитан! Мы с Хопкинсом перевезли вас на судно и, как могли, остановили кровь. Потом и доктора доставили - он вас наголо остричь хотел, но мы не позволили. Всё боялся, что мы его пристрелим, если вы Богу душу отдадите\nНо всё обошлось - вот вы уже и на ноги встали. Как себя чувствуете?";
        link.l1 = "Хм... дай минутку, соберусь с мыслями...(создание своего типа героя).";
        link.l1.go = "ChangePIRATES_Jess";
        link.l2 = "Да вроде уже ничего. Спасибо за заботу, Сандро.";
        link.l2.go = "Node_5_Jess";
        break;

    case "Node_5":
        dialog.text = "Ну, спиртного вам нельзя, а то, не ровен час, опять раздвоение начнется. А вот со шпагой поупражняться не помешало бы. Вы, небось, уже и забыли, с какого конца ее держать нужно.";
        link.l1 = "А ты знаешь, чем подцепить. Ну, давай попробуем, а то чувствую себя - " + GetSexPhrase("медведь медведем", "медведицей") + ".";
        link.l1.go = "Teach_1";
        link.l2 = "Не волнуйся, у меня же с головой проблемы были, а не с руками. Схожу-ка я в порт, а то одичал" + GetSexPhrase("", "а") + " совсем.";
        link.l2.go = "Finish_1";
        break;

    case "Node_5_Jess":
        dialog.text = "Ну вот видите, я знал, что всё будет в порядке... Но ранение в голову бесследно не проходит, потребуется время и упорство, чтоб восстановить свои силы и уменья. Не желаете руку размять - в фехтовании поупражняться?";
        link.l1 = "Хорошая идея. Давай-ка посмотрим, не совсем ли я расклеилась.";
        link.l1.go = "Teach_1_Jess";
        link.l2 = "Нет, не хочу. Я уверена в своих силах.";
        link.l2.go = "Finish_1";
        break;

    case "Finish_1":
        if (pchar.name == "Джессика")
        {
            dialog.text = "Мы сейчас в порту " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + ". Нужно как-то начинать новую жизнь без всех этих Масок и Белтропов, будь они неладны... То есть, пусть земля им будет пухом, я хотел сказать... А мы уж вас не подведём, капитан. Ваша команда останется с вами до конца.";
            link.l1 = "Ну что ж, значит - к новой мечте! Я вас не подведу и не разочарую. Все, я на берег.";
            link.l1.go = "Finish_2";
            link.l2 = "На смену одним мерзавцам появятся другие - такова жизнь, Сандро. Дашь мне пару советов, перед тем как я сойду на берег?";
            link.l2.go = "Advice_1";
        }
        else
        {
            dialog.text = "Мы сейчас в порту поселения " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + ", осваивайтесь, да возвращайтесь. Мы уж соскучились по настоящему делу - старый корабль продать пришлось, а на этом много не навоюешь. Так, перебивались в ожидании вашего выздоровления. А парни в вас верят, иначе бы разбежались давно...";
            link.l1 = "Замечательно. Все, я на берег... Да не волнуйся ты так, чай не маленьк" + GetSexPhrase("ий", "ая") + " - не заблужусь.";
            link.l1.go = "Finish_2";
            link.l2 = "Если считаешь, что я еще не готов" + GetSexPhrase("", "а") + " - говори. Дельный совет лишним не будет.";
            link.l2.go = "Advice_1";
        }
        break;

    case "Advice_1":
        dialog.text = "Ну что же, кэп... Нужно залатать корабль, пополнить экипаж да запастись припасами. И вперед, на поиски приключений! Лучше, конечно, получить каперский патент - тогда мы не будем вне закона, если займемся пиратством, а семьям своим сможем честно сказать, что работа наша - вполне легальна. А вы тогда сможете сделать неплохую карьеру и прославить свое имя.";
        link.l1 = "Что еще стоит знать?";
        link.l1.go = "Advice_2";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_2":
        dialog.text = "Чтобы торговать с выгодой, нужно знать, каковы текущие цены на товары в магазинах архипелага. Узнать их можно, посещая магазины лично, а можно спросить у встречных купцов в море или послушать слухи.";
        link.l1 = "Дальше.";
        link.l1.go = "Advice_3";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_3":
        dialog.text = "Орудия на корабле могут выйти из строя, и тогда их придется заменить. Можно также снять часть орудий и освободить дополнительное место под груз.";
        link.l1 = "Дальше.";
        link.l1.go = "Advice_4";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_4":
        dialog.text = "Если мы все-таки станем каперами, то учтите, что корабли, захваченные в море, продаются на верфи по бросовым ценам, тогда как честно купленные можно продать на другой верфи с неплохим барышом.";
        link.l1 = "Дальше.";
        link.l1.go = "Advice_5";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_5":
        dialog.text = "Не стоит портить отношения с контрабандистами почем зря - они обеспечивают хороший доход, пусть и с риском для здоровья.";
        link.l1 = "Дальше.";
        link.l1.go = "Advice_6";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_6":
        dialog.text = "Наймите офицеров, у нас вообще никого нет. Если авторитет ваш невысок, вы не сможете нанять много офицеров. В этом случае нанимайте тех, кто сможет занимать по две-три должности сразу. Трое таких всезнаек закроют нам все должности.";
        link.l1 = "Дальше.";
        link.l1.go = "Advice_7";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_7":
        dialog.text = "Воровство - штука неприглядная, но может случиться так, что вам очень нужно будет обчистить сундук в каком-нибудь доме, банке или магазине. Постарайтесь дождаться, когда хозяин отвернется, и только тогда лезьте в сундук. И помните - если хозяин внезапно обернется и увидит, что вы в его сундук залезли, то быть беде. Так что здесь нужно быть проворнее!";
        link.l1 = "Дальше.";
        link.l1.go = "Advice_8";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_8":
        dialog.text = "Возможно, вам понадобится проникнуть во вражеский город. Запомните хорошенько то, что я вам сейчас скажу - солдат в порту и на воротах, которые проверяют всех входящих в город, ночью нет! Так что заходить во вражеский город лучше ночью, а там уже знай - не попадайся патрулю. Патрульные солдаты, кстати, глаз на затылке не имеют и видят только впереди себя и по бокам. Ночью во вражеском городе пробирайтесь в таверну, переночуйте там до утра, а уже днем делайте свои дела. Но при передвижениях по городу держитесь от солдат подальше.";
        link.l1 = "Дальше.";
        link.l1.go = "Advice_9";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_9":
        dialog.text = "Еще можно поднять на корабле враждебный флаг, если он у вас есть, и уповать на свою удачу и скрытность. Ну, а самый надежный способ благополучно проникнуть во вражеский город - купить лицензию национальной торговой компании, в этом случае вас никто не задержит. Однако, не забудь флаг на корабле поднять соответствующий. Сами понимаете, глупо пытаться предъявить испанскую лицензию, если флаг на мачте - английский.";
        link.l1 = "Дальше.";
        link.l1.go = "Advice_10";
        link.l2 = "Замечательно. Все, я на берег.";
        link.l2.go = "Finish_2";
        break;

    case "Advice_10":
        dialog.text = "Знайте, что казематы находятся в фортах, в городах их не ищите.";
        link.l1 = "Спасибо. Мне пора на берег.";
        link.l1.go = "Finish_2";
        break;
    /////   фехт
    case "Teach_1":
        dialog.text = "Ну что же, начнем, пожалуй. У вас это всегда здорово получалось, но я напомню. Есть три атакующих удара: обычный удар, выпад и пробивной удар. Защитных действий тоже три: блок, парирование и финт. Есть еще защитно-атакующий круговой удар. И, конечно же, пистолет, чтобы противника издалека свинцовым талером угостить.";
        link.l1 = "Хорошо-хорошо, давай ближе к делу.";
        link.l1.go = "Teach_2";
        break;

    case "Teach_1_Jess":
        dialog.text = "Ну что же, начнем, пожалуй. У вас это всегда здорово получалось, но я напомню. Есть три атакующих удара: обычный удар, выпад и пробивной удар. Защитных действий тоже три: блок, парирование и финт. Есть еще защитно-атакующий круговой удар. И, конечно же, пистолет, чтобы противника издалека свинцовым талером угостить.";
        link.l1 = "Это ясно. Что дальше?";
        link.l1.go = "Teach_2";
        break;

    case "Teach_2":
        dialog.text = "Любое атакующее действие требует расхода энергии, на защитные действия энергия не расходуется. Можно также уклоняться от ударов, отскакивая назад и в стороны. Но так можно и пулю получить, если расстояние увеличится, и противник - не дурак.";
        link.l1 = "Дальше.";
        link.l1.go = "Teach_3";
        link.l2 = "Что такое энергия?";
        link.l2.go = "Teach_2_1";
        break;

    case "Teach_2_1":
        dialog.text = "Энергия - это показатель запаса сил персонажа в рукопашной схватке. Все атакующие действия требуют затрат энергии. Другими словами, в процессе схватки персонаж устает, и для восполнения сил ему требуется передышка. " +
                      "Максимальное значение энергии зависит от текущей величины реакции персонажа.";
        link.l1 = "Дальше.";
        link.l1.go = "Teach_3";
        break;

    case "Teach_3":
        dialog.text = "Во время схватки избегайте окружения большим количеством противников, иначе вас быстро порежут на бифштексы. Противостоять двоим еще можно, а вот троих и более сразу уложить - уже сложно. Когда энергия противников иссякнет, они начнут финты да парирование применять. Смотрите, не попадайтесь - быстро останетесь без головы.";
        link.l1 = "Дальше.";
        link.l1.go = "Teach_4";
        break;

    case "Teach_4":
        dialog.text = "Если соперник попался на ваш финт - он получит заметный урон, поболее, чем от колющего удара. Если же попасться на парирование, то можно и без энергии остаться. Собьют с ритма - и всех дел.";
        link.l1 = "Дальше.";
        link.l1.go = "Teach_5";
        break;

    case "Teach_5":
        dialog.text = "Оружие у всех разное, делится по весу на легкое, среднее и тяжелое. Вес оружия определяет расход энергии. Легеньким кинжалом можно без устали орудовать, зато тяжелым топором можно одним круговым ударом нескольких противников за раз на тот свет отправить.";
        link.l1 = "Дальше.";
        link.l1.go = "Teach_6";
        break;

    case "Teach_6":
        pchar.HeroParam.Teach_battle = 1;
        Tut_RestoreState();
        dialog.text = "Ну что, перейдем к практике? Предлагаю размять косточки. Биться будем по-настоящему, но не до смерти. Жизнь в бою можно эликсирами, зельями или ромом восстановить, но сейчас вы их лучше поберегите - будем тренироваться.";
        link.l1 = "Давай, пощады не жди!";
        link.l1.go = "Teach_battle_1";
        link.l2 = "Нет, спасибо. Я уже все понял" + GetSexPhrase("", "а") + ".";
        link.l2.go = "Finish_1";
        break;

    case "Teach_battle_lose":
        Tut_RestoreState();
        dialog.text = LinkRandPhrase("Да-а... Что-то совсем вы ослабели. Будьте внимательнее, больше блокируйте и парируйте. Пробивной не зевайте - от него блок не спасает, используйте финт, парирование или отскок.",
                                     "Не давайте себя ударить, перехватывайте удар противника колющим или парируйте. Но будьте осторожны, если попадетесь на финт - перехватят ваш колющий, да еще и тебе нанесут.",
                                     "Если энергия иссякнет - убегайте или отпрыгивайте, а противника доставайте финтом. Учтите, финтом удар так просто не отбить, но можно противника обмануть. И уж если попадется он на вашу уловку, да попытается на ваш обманный замах ударом ответить - тут вы не только его клинок от себя отведете, но и сами ему нанесете урон.") +
                      " Ну что, еще раз?";
        if (sti(pchar.rank) < 3) // чтоб не качались до упора
        {
            link.l1 = "Еще раз!";
            link.l1.go = "Teach_battle_1";
        }
        link.l2 = "Нет, достаточно. Я все понял" + GetSexPhrase("", "а") + ".";
        link.l2.go = "Finish_1";
        break;

    case "Teach_battle_win":
        pchar.HeroParam.Teach_battle = 2;
        Tut_RestoreState();
        dialog.text = "Хорошо. Молодец! Учтите, я дрался честно, но у врагов могут свои эликсиры жизни быть, тогда они будут не так легко даваться. " +
                      "Ну что, усложним задачу. Давайте против двоих противников?";
        link.l1 = "Что же, давай. Эй, Хопкинс! Хватай свой тесак и бегом на палубу!";
        link.l1.go = "Teach_battle_1";
        link.l2 = "Нет, спасибо. Я достаточно " + GetSexPhrase("потренировался", "потренировалась") + ".";
        link.l2.go = "Finish_1";
        break;

    case "Teach_battle_win_2":
        Tut_RestoreState();
        sld = characterFromID("Sailor_2");
        LAi_SetCitizenType(sld);
        if (pchar.name == "Джессика")
        {
            dialog.text = "Прекрасно, капитан! Уроки Белтропа не прошли бесследно, все же он неплохо вас обучил. И последний совет: чем больше вы фехтуете оружием одного типа, тем больше растет ваше умение. Хотите восстановить мастерство владения всеми видами - чаще меняйте тип оружия.";
        }
        else
        {
            dialog.text = "Да, с руками у вас все в порядке - не напрасно мы оружие прятали. И последний совет: чем больше вы фехтуете оружием одного типа, тем больше растет ваше умение. Хотите быть мастером во всех типах - чаще меняйте вид клинков.";
        }
        link.l1 = "Спасибо!";
        link.l1.go = "Finish_1";
        break;

    case "Teach_battle_win_3":
        Tut_RestoreState();
        sld = characterFromID("Sailor_2");
        LAi_SetCitizenType(sld);
        dialog.text = "Что же, неплохо. Одного противника вы одолели, но двое - не один. Тут сноровка нужна. Враги могут ведь втроем или вчетвером нападать. Повторим?";
        if (sti(pchar.rank) < 3) // чтоб не качались до упора
        {
            link.l1 = "Еще раз!";
            link.l1.go = "Teach_battle_1";
        }
        link.l2 = "Нет, я уже все понял" + GetSexPhrase("", "а") + ".";
        link.l2.go = "Finish_1";
        break;
    }
}
