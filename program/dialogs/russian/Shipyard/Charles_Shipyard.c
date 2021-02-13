// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, а и вообще в городе, я таких однообразно любознательных не видал.",
                                              "Ну что за вопросы? Мое дело - корабли строить, давайте этим и займемся.", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я " + GetSexPhrase("передумал", "передумала") + "...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                                           "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        // Addon 2016-1 Jason пиратская линейка
        if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
        {
            link.l1 = "Послушайте, мастер, вот вы строите корабли... и устанавливаете и заменяете паруса... а хорошим материалом для парусов... никогда не интересовались?";
            link.l1.go = "mtraxx";
        }
        break;

    // Addon 2016-1 Jason пиратская линейка
    case "mtraxx":
        dialog.text = "Какими-то загадками вы говорите, сударь... Давайте-ка начистоту и прямо - что у вас ко мне за предложение? И не бойтесь, я не портовый чинуша и не таможенная служба.";
        link.l1 = "Я вижу, с вами можно иметь дело! Речь идет о корабельном шелке. Из него, как мне известно, изготавливают самые лучшие паруса, которые повышают скорость судна...";
        link.l1.go = "mtraxx_1";
        break;

    case "mtraxx_1":
        dialog.text = "И не только скорость, но и ход в бейдевинд, если уж на то пошло. Вы хотели предложить мне приобрести у вас корабельный шелк? Безусловно, товар очень ценный. Но дело вот в чем: чтобы изготавливать из него паруса соответствующего качества, нужно уметь с ним работать. Вы понимаете, о чем я? Это не пеньковая парусина, и не имея нужных навыков, можно попросту испортить дорогостоящий товар. Я с ним не работаю и никогда не работал. Вообще, моя верфь имеет другой профиль, и, предложи вы мне канаты из Московии, я бы наверняка заключил с вами сделку. Мое производство постоянно нуждается в них. А шелк мне не нужен, увы!";
        link.l1 = "Хм. Ясно. Ну, спасибо что хоть выслушали, мастер. Удачи!";
        link.l1.go = "mtraxx_2";
        break;

    case "mtraxx_2":
        DialogExit();
        AddQuestRecord("Roger_2", "4");
        pchar.questTemp.Mtraxx = "silk_3";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
