/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/lab_item.c. */

#include "lab_item.h"
#include "hal_libc.h"
typedef struct OneByte {
    char c[1];
} OneByte;

char* func_8002E160_jp(s32 item_id, char* dest);
s32 LabItem_IsQuantitylessItem(s32 arg0);
s32 LabItem_IsQuantitylessItemForOperation(s32 arg0);

// Copies the Japanese description of Generation I item `item_id` into `dest`, or an empty string
// when the id is outside 0-255 or has no description. Returns `dest`.
char* func_8002E160_jp(s32 item_id, char* dest) {
    // Indexed by item id (1 = Master Ball, 196-200 = HM01-05, 201-250 = TM01-50). Ids without an
    // item are NULL; 7 (Surfboard) and 9 (Pokedex) point to empty descriptions.
    static char* s_item_descriptions[256] = {
        NULL,
        "やせいのポケモンを　１００パーセント\nかくじつに　つかまえられる　ボール。", // Master Ball: "A ball that catches a wild Pokemon 100% of the time."
        "スーパーボールよりも　ポケモンが\nつかまりやすくなる　ボール。", // Ultra Ball: "A ball that catches Pokemon more easily than a Great Ball."
        "モンスターボールよりも　ポケモンが\nつかまりやすくなる　ボール。", // Great Ball: "A ball that catches Pokemon more easily than a Poke Ball."
        "やせいのポケモンを　つかまえるときに\nこのボールを　なげつける。", // Poke Ball: "A ball thrown to catch a wild Pokemon."
        "まちの　ちず。じぶんが　いま\nどこにいるかが　わかる。", // Town Map: "A map of the region. Shows where you are now."
        "あるくときの　２ばいの　はやさで\nいどう　することが　できる。", // Bicycle: "Lets you move at twice walking speed."
        "",
        "サファリゾーンで　やせいのポケモンを\nつかまえるときに　つかう　ボール。", // Safari Ball: "A ball used to catch wild Pokemon in the Safari Zone."
        "",
        "ある　とくていの　ポケモンを\nしんかさせる　いし。", // Moon Stone: "A stone that makes certain Pokemon evolve."
        "どく　じょうたいのときに　つかえば\nどくを　けしてくれる。", // Antidote: "Cures a poisoned Pokemon."
        "やけど　じょうたいのときに　つかえば\nやけどを　なおしてくれる。", // Burn Heal: "Heals a burned Pokemon."
        "こおり　じょうたいのときに　つかえば\nこおりを　とかしてくれる。", // Ice Heal: "Thaws a frozen Pokemon."
        "ねむり　じょうたいのときに　つかえば\nめを　さましてくれる。", // Awakening: "Wakes up a sleeping Pokemon."
        "まひ　じょうたいのときに　つかえば\nまひを　といてくれる。", // Parlyz Heal: "Cures a paralyzed Pokemon."
        "ＨＰを　まんたんにし　どく　などの\nとくしゅじょうたいも　なおしてくれる。", // Full Restore: "Fully restores HP and also cures poison and other status problems."
        "たたかいで　うしなった\nＨＰを　まんたんに　する。", // Max Potion: "Fully restores HP lost in battle."
        "たたかいで　うしなった\nＨＰを　２００かいふく　する。", // Hyper Potion: "Restores 200 HP lost in battle."
        "たたかいで　うしなった\nＨＰを　５０かいふく　する。", // Super Potion: "Restores 50 HP lost in battle."
        "たたかいで　うしなった\nＨＰを　２０かいふく　する。", // Potion: "Restores 20 HP lost in battle."
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "どうくつなどから　さいごに　やすんだ　　\nポケモンセンターに　もどる。　", // Escape Rope: "Returns you from a cave or similar place to the last Pokemon Center you rested at."
        "フィールドで　ポケモンが\nちかよって　こなくなる。　", // Repel: "Keeps wild Pokemon from approaching in the field."
        "おおむかしに　き　からでた\nじゅえきが　かたまったもの。", // Old Amber: "Sap from an ancient tree that has hardened."
        "ある　とくていの　ポケモンを\nしんかさせる　いし。", // Fire Stone: "A stone that makes certain Pokemon evolve."
        "ある　とくていの　ポケモンを\nしんかさせる　いし。", // Thunder Stone: "A stone that makes certain Pokemon evolve."
        "ある　とくていの　ポケモンを\nしんかさせる　いし。", // Water Stone: "A stone that makes certain Pokemon evolve."
        "つかうと　ポケモンの\nＨＰの　さいだいちが　ふえる。", // HP Up: "Raises a Pokemon's maximum HP."
        "つかうと　ポケモンの　こうげきりょく\nの　きそポイントが　あがる。", // Protein: "Raises the base points of a Pokemon's Attack."
        "つかうと　ポケモンの　ぼうぎょりょく\nの　きそポイントが　あがる。", // Iron: "Raises the base points of a Pokemon's Defense."
        "つかうと　ポケモンの　すばやさの\nきそポイントが　あがる。", // Carbos: "Raises the base points of a Pokemon's Speed."
        "つかうと　ポケモンの　とくしゅ\nのうりょくの　きそポイントがあがる。", // Calcium: "Raises the base points of a Pokemon's Special."
        "つかうと　ポケモンの\nレベルが　１つ　あがる。", // Rare Candy: "Raises a Pokemon's level by 1."
        "おおむかしに　いきていた\nポケモンの　かせき。", // Dome Fossil: "The fossil of a Pokemon that lived long ago."
        "おおむかしに　いきていた\nポケモンの　かせき。", // Helix Fossil: "The fossil of a Pokemon that lived long ago."
        "どこかにある　ポケモンジムの\nドアの　カギ。", // Secret Key: "The key to the door of a Pokemon Gym somewhere."
        "",
        "ハナダシティの　ミラクル・サイクルで\nじてんしゃと　こうかんできる。", // Bike Voucher: "Can be exchanged for a bicycle at the Miracle Cycle in Cerulean City."
        "そのたたかいの　あいだだけ\nこうげきが　あたりやすくなる。", // X Accuracy: "Raises accuracy for the rest of the battle."
        "ある　とくていの　ポケモンを\nしんかさせる　いし。", // Leaf Stone: "A stone that makes certain Pokemon evolve."
        "どこかにある　ビルの　ドアロックを\nあける　カードキー。", // Card Key: "A card key that opens the door locks of a building somewhere."
        "フレンドリィショップに　もっていくと\nたかいねだんで　かいとってくれる。", // Nugget: "The Poke Mart will buy it for a high price."
        "",
        "たたかいのときに　つかうと　かならず\nにげることが　できる。", // Poke Doll: "Used in battle, it always lets you run away."
        "ひんし いがいの　いろいろな　とくしゅ\nじょうたいを　なおしてくれる。", // Full Heal: "Cures all status problems except fainting."
        "ひんしのポケモンのＨＰを　さいだいち\nの　はんぶん　かいふくする。　", // Revive: "Revives a fainted Pokemon with half of its maximum HP."
        "ひんしじょうたいの　ポケモンのＨＰを\nまんたんに　してくれる。", // Max Revive: "Revives a fainted Pokemon with full HP."
        "そのたたかいの　あいだだけ　あいての\nとくしゅこうげきを　ふせいでくれる。", // Guard Spec.: "Protects against the foe's special attacks for the rest of the battle."
        "ポケモンが　ちかよらなくなる。\nむしよけスプレーより　ながく　きく。", // Super Repel: "Keeps Pokemon away. Lasts longer than Repel."
        "ポケモンが　ちかよらなくなる。\nシルバースプレーより　ながく　きく。", // Max Repel: "Keeps Pokemon away. Lasts longer than Super Repel."
        "そのたたかいの　あいだだけ　こうげき\nが　きゅうしょに　あたりやすくなる。", // Dire Hit: "Makes critical hits more likely for the rest of the battle."
        "",
        "つかうと　ポケモンの\nＨＰを　５０かいふくしてくれる。", // Fresh Water: "Restores 50 HP."
        "つかうと　ポケモンの\nＨＰを　６０かいふくしてくれる。", // Soda Pop: "Restores 60 HP."
        "つかうと　ポケモンの\nＨＰを　８０かいふくしてくれる。", // Lemonade: "Restores 80 HP."
        "ごうかきゃくせん　サント・アンヌごう\nに　のることが　できる。", // S.S. Ticket: "Lets you board the luxury liner S.S. Anne."
        "サファリゾーンの　えんちょうが\nなくして　こまっているらしい。", // Gold Teeth: "The Safari Zone warden seems troubled after losing them."
        "そのたたかいの　あいだだけ　こうげき\nりょくを　あげてくれる。", // X Attack: "Raises Attack for the rest of the battle."
        "そのたたかいの　あいだだけ　ぼうぎょ\nりょくを　あげてくれる。", // X Defend: "Raises Defense for the rest of the battle."
        "そのたたかいの　あいだだけ　すばやさ\nを　あげてくれる。", // X Speed: "Raises Speed for the rest of the battle."
        "そのたたかいの　あいだだけ　とくしゅ\nのうりょくを　あげてくれる。", // X Special: "Raises Special for the rest of the battle."
        "スロットマシンで　あそべるようになる。\nさいだい９９９９まで　コインをもてる。", // Coin Case: "Lets you play the slot machines. Holds up to 9999 coins."
        "フレンドリィショップで　たのまれた\nオーキドはかせへの　おとどけもの。", // Oak's Parcel: "A delivery for Professor Oak, requested at the Poke Mart."
        "フィールドに　おちている　どうぐを\nさがすときに　つかう。", // Itemfinder: "Used to search for items lying in the field."
        "ゆうれいの　しょうたいを\nはっきりと　うつしだす。", // Silph Scope: "Clearly reveals the true identity of ghosts."
        "ふくと　ここちよい　おんがくが\nながれ　ポケモンが　めをさます。", // Poke Flute: "Plays soothing music that wakes up Pokemon."
        "どこかの　エレベータを\nうごかすときに　つかう。", // Lift Key: "Used to run an elevator somewhere."
        "そのたたかいに　さんかしなかった\nポケモンにも　けいけんちを　わける。", // Exp. All: "Shares experience points with Pokemon that did not take part in the battle."
        "うみや　かわで　つかうと\nポケモンが　つれる。", // Old Rod: "Used at sea or in rivers to fish up Pokemon."
        "うみや　かわで　つかうと\nポケモンが　つれる。　", // Good Rod: "Used at sea or in rivers to fish up Pokemon."
        "うみや　かわで　つかうと\nポケモンが　つれる。", // Super Rod: "Used at sea or in rivers to fish up Pokemon."
        "つかうと　ポケモンの\nＰＰの　さいだいちが　２わりふえる。", // PP Up: "Raises a move's maximum PP by 20%."
        "ひとつの　わざだけ　ＰＰを\n１０　かいふくしてくれる。", // Ether: "Restores 10 PP of one move."
        "ひとつの　わざだけ　ＰＰを\nぜんぶ　かいふくしてくれる。", // Max Ether: "Fully restores the PP of one move."
        "ポケモン１ぴきの　すべての　わざの\nＰＰを　１０　かいふくする。", // Elixer: "Restores 10 PP of every move of one Pokemon."
        "ポケモン１ぴきの　すべての　わざの\nＰＰを　ぜんぶ　かいふくする。", // Max Elixer: "Fully restores the PP of every move of one Pokemon."
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "いあいぎり　　　ノーマル　ＰＰ／３０\nいりょく／５０　　めいちゅう／９５", // HM01 Cut: "Cut  Normal  PP/30  Power/50  Accuracy/95"
        "そらをとぶ　　　ひこう　　ＰＰ／１５\nいりょく／７０　　めいちゅう／９５", // HM02 Fly: "Fly  Flying  PP/15  Power/70  Accuracy/95"
        "なみのり　　　　みず　　　ＰＰ／１５\nいりょく／９５　　めいちゅう／１００", // HM03 Surf: "Surf  Water  PP/15  Power/95  Accuracy/100"
        "かいりき　　　　ノーマル　ＰＰ／１５\nいりょく／８０　　めいちゅう／１００", // HM04 Strength: "Strength  Normal  PP/15  Power/80  Accuracy/100"
        "フラッシュ　　　ノーマル　ＰＰ／２０\nいりょく／−−　　めいちゅう／７０", // HM05 Flash: "Flash  Normal  PP/20  Power/--  Accuracy/70"
        "メガトンパンチ　ノーマル　ＰＰ／２０\nいりょく／８０　　めいちゅう／８５", // TM01 Mega Punch: "Mega Punch  Normal  PP/20  Power/80  Accuracy/85"
        "かまいたち　　　ノーマル　ＰＰ／１０\nいりょく／８０　　めいちゅう／７５", // TM02 Razor Wind: "Razor Wind  Normal  PP/10  Power/80  Accuracy/75"
        "つるぎのまい　　ノーマル　ＰＰ／３０\nいりょく／−−　　めいちゅう／１００", // TM03 Swords Dance: "Swords Dance  Normal  PP/30  Power/--  Accuracy/100"
        "ふきとばし　　　ノーマル　ＰＰ／２０\nいりょく／−−　　めいちゅう／８５", // TM04 Whirlwind: "Whirlwind  Normal  PP/20  Power/--  Accuracy/85"
        "メガトンキック　ノーマル　ＰＰ／５\nいりょく／１２０　めいちゅう／７５", // TM05 Mega Kick: "Mega Kick  Normal  PP/5  Power/120  Accuracy/75"
        "どくどく　　　　どく　　　ＰＰ／１０\nいりょく／−−　　めいちゅう／８５", // TM06 Toxic: "Toxic  Poison  PP/10  Power/--  Accuracy/85"
        "つのドリル　　　ノーマル　ＰＰ／５  \nいりょく／−−　　めいちゅう／３０", // TM07 Horn Drill: "Horn Drill  Normal  PP/5  Power/--  Accuracy/30"
        "のしかかり　　　ノーマル　ＰＰ／１５\nいりょく／８５　　めいちゅう／１００", // TM08 Body Slam: "Body Slam  Normal  PP/15  Power/85  Accuracy/100"
        "とっしん　　　　ノーマル　ＰＰ／２０\nいりょく／９０　　めいちゅう／８５", // TM09 Take Down: "Take Down  Normal  PP/20  Power/90  Accuracy/85"
        "すてみタックル　ノーマル　ＰＰ／１５\nいりょく／１００　めいちゅう／１００", // TM10 Double-Edge: "Double-Edge  Normal  PP/15  Power/100  Accuracy/100"
        "バブルこうせん　みず　　　ＰＰ／２０\nいりょく／６５　　めいちゅう／１００", // TM11 BubbleBeam: "BubbleBeam  Water  PP/20  Power/65  Accuracy/100"
        "みずでっぽう　　みず　　　ＰＰ／２５\nいりょく／４０　　めいちゅう／１００", // TM12 Water Gun: "Water Gun  Water  PP/25  Power/40  Accuracy/100"
        "れいとうビーム　こおり　　ＰＰ／１０\nいりょく／９５　　めいちゅう／１００", // TM13 Ice Beam: "Ice Beam  Ice  PP/10  Power/95  Accuracy/100"
        "ふぶき　　　　　こおり　　ＰＰ／５\nいりょく／１２０　めいちゅう／９０", // TM14 Blizzard: "Blizzard  Ice  PP/5  Power/120  Accuracy/90"
        "はかいこうせん　ノーマル　ＰＰ／５\nいりょく／１５０　めいちゅう／９０", // TM15 Hyper Beam: "Hyper Beam  Normal  PP/5  Power/150  Accuracy/90"
        "ねこにこばん　　ノーマル　ＰＰ／２０\nいりょく／４０　　めいちゅう／１００", // TM16 Pay Day: "Pay Day  Normal  PP/20  Power/40  Accuracy/100"
        "じごくぐるま　　かくとう　ＰＰ／２５\nいりょく／８０　　めいちゅう／８０", // TM17 Submission: "Submission  Fighting  PP/25  Power/80  Accuracy/80"
        "カウンター　　　かくとう　ＰＰ／２０\nいりょく／−−　　めいちゅう／１００", // TM18 Counter: "Counter  Fighting  PP/20  Power/--  Accuracy/100"
        "ちきゅうなげ　　かくとう　ＰＰ／２０\nいりょく／−−　　めいちゅう／１００", // TM19 Seismic Toss: "Seismic Toss  Fighting  PP/20  Power/--  Accuracy/100"
        "いかり　　　　　ノーマル　ＰＰ／２０\nいりょく／２０　　めいちゅう／１００", // TM20 Rage: "Rage  Normal  PP/20  Power/20  Accuracy/100"
        "メガドレイン　　くさ　　　ＰＰ／１０\nいりょく／４０　　めいちゅう／１００", // TM21 Mega Drain: "Mega Drain  Grass  PP/10  Power/40  Accuracy/100"
        "ソーラービーム　くさ　　　ＰＰ／１０\nいりょく／１２０　めいちゅう／１００", // TM22 SolarBeam: "SolarBeam  Grass  PP/10  Power/120  Accuracy/100"
        "りゅうのいかり　ドラゴン　ＰＰ／１０\nいりょく／−−　　めいちゅう／１００", // TM23 Dragon Rage: "Dragon Rage  Dragon  PP/10  Power/--  Accuracy/100"
        "１０まんボルト　でんき　　ＰＰ／１５\nいりょく／９５　　めいちゅう／１００", // TM24 Thunderbolt: "Thunderbolt  Electric  PP/15  Power/95  Accuracy/100"
        "かみなり　　　　でんき　　ＰＰ／１０\nいりょく／１２０　めいちゅう／７０", // TM25 Thunder: "Thunder  Electric  PP/10  Power/120  Accuracy/70"
        "じしん　　　　　じめん　　ＰＰ／１０\nいりょく／１００　めいちゅう／１００", // TM26 Earthquake: "Earthquake  Ground  PP/10  Power/100  Accuracy/100"
        "じわれ　　　　　じめん　　ＰＰ／５\nいりょく／−−　　めいちゅう／３０", // TM27 Fissure: "Fissure  Ground  PP/5  Power/--  Accuracy/30"
        "あなをほる　　　じめん　　ＰＰ／１０\nいりょく／１００　めいちゅう／１００", // TM28 Dig: "Dig  Ground  PP/10  Power/100  Accuracy/100"
        "サイコキネシス　エスパー　ＰＰ／１０\nいりょく／９０　　めいちゅう／１００", // TM29 Psychic: "Psychic  Psychic  PP/10  Power/90  Accuracy/100"
        "テレポート　　　エスパー　ＰＰ／２０\nいりょく／−−　　めいちゅう／１００", // TM30 Teleport: "Teleport  Psychic  PP/20  Power/--  Accuracy/100"
        "ものまね　　　　ノーマル　ＰＰ／１０\nいりょく／−−　　めいちゅう／１００", // TM31 Mimic: "Mimic  Normal  PP/10  Power/--  Accuracy/100"
        "かげぶんしん　　ノーマル　ＰＰ／１５\nいりょく／−−　　めいちゅう／１００", // TM32 Double Team: "Double Team  Normal  PP/15  Power/--  Accuracy/100"
        "リフレクター　　エスパー　ＰＰ／２０\nいりょく／−−　　めいちゅう／１００", // TM33 Reflect: "Reflect  Psychic  PP/20  Power/--  Accuracy/100"
        "がまん　　　　　ノーマル　ＰＰ／１０\nいりょく／−−　　めいちゅう／１００", // TM34 Bide: "Bide  Normal  PP/10  Power/--  Accuracy/100"
        "ゆびをふる　　　ノーマル　ＰＰ／１０\nいりょく／−−　　めいちゅう／１００", // TM35 Metronome: "Metronome  Normal  PP/10  Power/--  Accuracy/100"
        "じばく　　　　　ノーマル　ＰＰ／５\nいりょく／１３０　めいちゅう／１００", // TM36 Selfdestruct: "Selfdestruct  Normal  PP/5  Power/130  Accuracy/100"
        "タマゴばくだん　ノーマル　ＰＰ／１０\nいりょく／１００　めいちゅう／７５", // TM37 Egg Bomb: "Egg Bomb  Normal  PP/10  Power/100  Accuracy/75"
        "だいもんじ　　　ほのお　　ＰＰ／５\nいりょく／１２０　めいちゅう／８５", // TM38 Fire Blast: "Fire Blast  Fire  PP/5  Power/120  Accuracy/85"
        "スピードスター　ノーマル　ＰＰ／２０\nいりょく／６０　　めいちゅう／１００", // TM39 Swift: "Swift  Normal  PP/20  Power/60  Accuracy/100"
        "ロケットずつき　ノーマル　ＰＰ／１５\nいりょく／１００　めいちゅう／１００", // TM40 Skull Bash: "Skull Bash  Normal  PP/15  Power/100  Accuracy/100"
        "タマゴうみ　　　ノーマル　ＰＰ／１０\nいりょく／−−　　めいちゅう／１００", // TM41 Softboiled: "Softboiled  Normal  PP/10  Power/--  Accuracy/100"
        "ゆめくい　　　　エスパー　ＰＰ／１５\nいりょく／１００　めいちゅう／１００", // TM42 Dream Eater: "Dream Eater  Psychic  PP/15  Power/100  Accuracy/100"
        "ゴッドバード　　ひこう　　ＰＰ／５\nいりょく／１４０　めいちゅう／９０", // TM43 Sky Attack: "Sky Attack  Flying  PP/5  Power/140  Accuracy/90"
        "ねむる　　　　　エスパー　ＰＰ／１０\nいりょく／−−　　めいちゅう／１００", // TM44 Rest: "Rest  Psychic  PP/10  Power/--  Accuracy/100"
        "でんじは　　　　でんき　　ＰＰ／２０\nいりょく／−−　　めいちゅう／１００", // TM45 Thunder Wave: "Thunder Wave  Electric  PP/20  Power/--  Accuracy/100"
        "サイコウェーブ　エスパー　ＰＰ／１５\nいりょく／−−　　めいちゅう／８０", // TM46 Psywave: "Psywave  Psychic  PP/15  Power/--  Accuracy/80"
        "だいばくはつ　　ノーマル　ＰＰ／５\nいりょく／１７０　めいちゅう／１００", // TM47 Explosion: "Explosion  Normal  PP/5  Power/170  Accuracy/100"
        "いわなだれ　　　いわ　　　ＰＰ／１０\nいりょく／７５　　めいちゅう／９０", // TM48 Rock Slide: "Rock Slide  Rock  PP/10  Power/75  Accuracy/90"
        "トライアタック　ノーマル　ＰＰ／１０\nいりょく／８０　　めいちゅう／１００", // TM49 Tri Attack: "Tri Attack  Normal  PP/10  Power/80  Accuracy/100"
        "みがわり　　　　ノーマル　ＰＰ／１０\nいりょく／−−　　めいちゅう／１００", // TM50 Substitute: "Substitute  Normal  PP/10  Power/--  Accuracy/100"
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };

    if ((item_id < 0) || (item_id >= 256) || (s_item_descriptions[item_id] == NULL)) {
        // FAKE: copying the "" literal as a one-byte struct makes IDO load its address before the
        // lbu; a plain char assignment folds %lo into the lbu.
        *(OneByte*)dest = *(OneByte*)"";
    } else {
        HAL_Strcpy(dest, s_item_descriptions[item_id]);
    }
    return dest;
}

/** Returns whether an item has no quantity. */
s32 LabItem_IsQuantitylessItem(s32 arg0) {
    static u8 D_80075950[] = {
        5,    6,    8,    9,    0x1F, 0x29, 0x2A, 0x2B, 0x2D, 0x30, 0x3F, 0x40, 0x45,
        0x46, 0x47, 0x48, 0x49, 0x4A, 0x4C, 0x4D, 0x4E, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
    };

    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80075950); i++) {
        if (arg0 == D_80075950[i]) {
            return 1;
        }
    }

    return 0;
}

/** Returns whether an item has no quantity for the requested operation. */
s32 LabItem_IsQuantitylessItemForOperation(s32 arg0) {
    s32 sp1C = 0;

    if (LabItem_IsQuantitylessItem(arg0) != 0) {
        sp1C = 1;
    }
    return sp1C;
}
