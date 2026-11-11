# Gen 1 Japanese → English glossary

Pocket Monsters Stadium (ポケモンスタジアム, 1998) only ships Japanese text. Annotations in this repo use the
**official English localized names** instead, e.g. フーディン → Alakazam, モンスターボール → Poké Ball,
だいもんじ → Fire Blast. Use this file to look names up while reading in-game text or data tables.

## Conventions

- **English** is the current official English name (modern capitalization, e.g. `Thunder Shock`). Where the Gen 1 English games (Red/Blue/Yellow) spelled it differently, that spelling is in the *RBY spelling* column. Prefer the original name in identifiers and comments: `THUNDERSHOCK`, `POKE_BALL`, `ALAKAZAM`.
- **Romanization** is plain Hepburn without macrons (long vowels doubled, `ー` repeats the vowel), generated mechanically from the kana. It is a search aid, not an official name. For Pokémon, the *Trademark romaji* column also gives Nintendo's registered romanization (e.g. Foodin, Barrierd).
- Kana is as written in Gen 1–era Japanese text. Where Stadium Zero spells something differently, the table
  gives Zero's spelling (オツキミやま, ななしのどうくつ, クリティカッター, シージー). Game text uses fullwidth digits.
- **Zero ✓** marks a Japanese string that appears in Stadium Zero's own text in exactly that form. This was
  checked by a ROM text audit of PR #53 on 2026-11-11 (Pokémon names, categories, moves, move types, items,
  TM/HM moves, map labels, tournament opponents and labels). Rows without the mark are general Gen 1
  reference vocabulary. They are still correct series terms, but Zero's text was not found to contain them.
  The audit checks only the Japanese. English spellings, trademark romaji and kanji are outside its scope.
- Sources: the Pokémon, move, item and type tables are generated from the [PokeAPI](https://github.com/PokeAPI/pokeapi) CSV data (Japanese kana, English names, Gen 1 item indices). The people, places, game-term and Stadium sections are hand-written; entries marked ⚠ are unverified and should be checked against the in-game text.

## Contents

- [Pokémon](#pokémon)
- [Types](#types)
- [Moves](#moves)
- [Items](#items)
- [TMs and HMs](#tms-and-hms)
- [Stats and status conditions](#stats-and-status-conditions)
- [Battle messages and game terms](#battle-messages-and-game-terms)
- [People](#people)
- [Trainer classes](#trainer-classes)
- [Places](#places)
- [Stadium modes and features](#stadium-modes-and-features)
- [Nintendo Cup '97 finalists](#nintendo-cup-97-finalists-locked-romanizations)

## Pokémon

Dex numbers are National Pokédex order. All 151 names and 150 of 151 categories match Zero's species table; Porygon's category in Zero is シージー ("CG"), shown as シージーポケモン. Its English category stays Virtual Pokémon. Gen 1 cartridges store
species by an internal index that is *not* dex order; map through dex number.

| # | Japanese | Romanization | Trademark romaji | English | Category (JP) | Category (EN) |
|---:|---|---|---|---|---|---|
| 001 | フシギダネ | Fushigidane | Fushigidane | Bulbasaur | たねポケモン | Seed Pokémon |
| 002 | フシギソウ | Fushigisou | Fushigisou | Ivysaur | たねポケモン | Seed Pokémon |
| 003 | フシギバナ | Fushigibana | Fushigibana | Venusaur | たねポケモン | Seed Pokémon |
| 004 | ヒトカゲ | Hitokage | Hitokage | Charmander | とかげポケモン | Lizard Pokémon |
| 005 | リザード | Rizaado | Lizardo | Charmeleon | かえんポケモン | Flame Pokémon |
| 006 | リザードン | Rizaadon | Lizardon | Charizard | かえんポケモン | Flame Pokémon |
| 007 | ゼニガメ | Zenigame | Zenigame | Squirtle | かめのこポケモン | Tiny Turtle Pokémon |
| 008 | カメール | Kameeru | Kameil | Wartortle | かめポケモン | Turtle Pokémon |
| 009 | カメックス | Kamekkusu | Kamex | Blastoise | こうらポケモン | Shellfish Pokémon |
| 010 | キャタピー | Kyatapii | Caterpie | Caterpie | いもむしポケモン | Worm Pokémon |
| 011 | トランセル | Toranseru | Transel | Metapod | さなぎポケモン | Cocoon Pokémon |
| 012 | バタフリー | Batafurii | Butterfree | Butterfree | ちょうちょポケモン | Butterfly Pokémon |
| 013 | ビードル | Biidoru | Beedle | Weedle | けむしポケモン | Hairy Bug Pokémon |
| 014 | コクーン | Kokuun | Cocoon | Kakuna | さなぎポケモン | Cocoon Pokémon |
| 015 | スピアー | Supiaa | Spear | Beedrill | どくばちポケモン | Poison Bee Pokémon |
| 016 | ポッポ | Poppo | Poppo | Pidgey | ことりポケモン | Tiny Bird Pokémon |
| 017 | ピジョン | Pijon | Pigeon | Pidgeotto | とりポケモン | Bird Pokémon |
| 018 | ピジョット | Pijotto | Pigeot | Pidgeot | とりポケモン | Bird Pokémon |
| 019 | コラッタ | Koratta | Koratta | Rattata | ねずみポケモン | Mouse Pokémon |
| 020 | ラッタ | Ratta | Ratta | Raticate | ねずみポケモン | Mouse Pokémon |
| 021 | オニスズメ | Onisuzume | Onisuzume | Spearow | ことりポケモン | Tiny Bird Pokémon |
| 022 | オニドリル | Onidoriru | Onidrill | Fearow | くちばしポケモン | Beak Pokémon |
| 023 | アーボ | Aabo | Arbo | Ekans | へびポケモン | Snake Pokémon |
| 024 | アーボック | Aabokku | Arbok | Arbok | コブラポケモン | Cobra Pokémon |
| 025 | ピカチュウ | Pikachuu | Pikachu | Pikachu | ねずみポケモン | Mouse Pokémon |
| 026 | ライチュウ | Raichuu | Raichu | Raichu | ねずみポケモン | Mouse Pokémon |
| 027 | サンド | Sando | Sand | Sandshrew | ねずみポケモン | Mouse Pokémon |
| 028 | サンドパン | Sandopan | Sandpan | Sandslash | ねずみポケモン | Mouse Pokémon |
| 029 | ニドラン♀ | Nidoran♀ | Nidoran♀ | Nidoran♀ | どくばりポケモン | Poison Pin Pokémon |
| 030 | ニドリーナ | Nidoriina | Nidorina | Nidorina | どくばりポケモン | Poison Pin Pokémon |
| 031 | ニドクイン | Nidokuin | Nidoqueen | Nidoqueen | ドリルポケモン | Drill Pokémon |
| 032 | ニドラン♂ | Nidoran♂ | Nidoran♂ | Nidoran♂ | どくばりポケモン | Poison Pin Pokémon |
| 033 | ニドリーノ | Nidoriino | Nidorino | Nidorino | どくばりポケモン | Poison Pin Pokémon |
| 034 | ニドキング | Nidokingu | Nidoking | Nidoking | ドリルポケモン | Drill Pokémon |
| 035 | ピッピ | Pippi | Pippi | Clefairy | ようせいポケモン | Fairy Pokémon |
| 036 | ピクシー | Pikushii | Pixy | Clefable | ようせいポケモン | Fairy Pokémon |
| 037 | ロコン | Rokon | Rokon | Vulpix | きつねポケモン | Fox Pokémon |
| 038 | キュウコン | Kyuukon | Kyukon | Ninetales | きつねポケモン | Fox Pokémon |
| 039 | プリン | Purin | Purin | Jigglypuff | ふうせんポケモン | Balloon Pokémon |
| 040 | プクリン | Pukurin | Pukurin | Wigglytuff | ふうせんポケモン | Balloon Pokémon |
| 041 | ズバット | Zubatto | Zubat | Zubat | こうもりポケモン | Bat Pokémon |
| 042 | ゴルバット | Gorubatto | Golbat | Golbat | こうもりポケモン | Bat Pokémon |
| 043 | ナゾノクサ | Nazonokusa | Nazonokusa | Oddish | ざっそうポケモン | Weed Pokémon |
| 044 | クサイハナ | Kusaihana | Kusaihana | Gloom | ざっそうポケモン | Weed Pokémon |
| 045 | ラフレシア | Rafureshia | Ruffresia | Vileplume | フラワーポケモン | Flower Pokémon |
| 046 | パラス | Parasu | Paras | Paras | きのこポケモン | Mushroom Pokémon |
| 047 | パラセクト | Parasekuto | Parasect | Parasect | きのこポケモン | Mushroom Pokémon |
| 048 | コンパン | Konpan | Kongpang | Venonat | こんちゅうポケモン | Insect Pokémon |
| 049 | モルフォン | Morufon | Morphon | Venomoth | どくがポケモン | Poison Moth Pokémon |
| 050 | ディグダ | Diguda | Digda | Diglett | もぐらポケモン | Mole Pokémon |
| 051 | ダグトリオ | Dagutorio | Dugtrio | Dugtrio | もぐらポケモン | Mole Pokémon |
| 052 | ニャース | Nyaasu | Nyarth | Meowth | ばけねこポケモン | Scratch Cat Pokémon |
| 053 | ペルシアン | Perushian | Persian | Persian | シャムネコポケモン | Classy Cat Pokémon |
| 054 | コダック | Kodakku | Koduck | Psyduck | あひるポケモン | Duck Pokémon |
| 055 | ゴルダック | Gorudakku | Golduck | Golduck | あひるポケモン | Duck Pokémon |
| 056 | マンキー | Mankii | Mankey | Mankey | ぶたざるポケモン | Pig Monkey Pokémon |
| 057 | オコリザル | Okorizaru | Okorizaru | Primeape | ぶたざるポケモン | Pig Monkey Pokémon |
| 058 | ガーディ | Gaadi | Gardie | Growlithe | こいぬポケモン | Puppy Pokémon |
| 059 | ウインディ | Uindi | Windie | Arcanine | でんせつポケモン | Legendary Pokémon |
| 060 | ニョロモ | Nyoromo | Nyoromo | Poliwag | おたまポケモン | Tadpole Pokémon |
| 061 | ニョロゾ | Nyorozo | Nyorozo | Poliwhirl | おたまポケモン | Tadpole Pokémon |
| 062 | ニョロボン | Nyorobon | Nyorobon | Poliwrath | おたまポケモン | Tadpole Pokémon |
| 063 | ケーシィ | Keeshi | Casey | Abra | ねんりきポケモン | Psi Pokémon |
| 064 | ユンゲラー | Yungeraa | Yungerer | Kadabra | ねんりきポケモン | Psi Pokémon |
| 065 | フーディン | Fuudin | Foodin | Alakazam | ねんりきポケモン | Psi Pokémon |
| 066 | ワンリキー | Wanrikii | Wanriky | Machop | かいりきポケモン | Superpower Pokémon |
| 067 | ゴーリキー | Goorikii | Goriky | Machoke | かいりきポケモン | Superpower Pokémon |
| 068 | カイリキー | Kairikii | Kairiky | Machamp | かいりきポケモン | Superpower Pokémon |
| 069 | マダツボミ | Madatsubomi | Madatsubomi | Bellsprout | フラワーポケモン | Flower Pokémon |
| 070 | ウツドン | Utsudon | Utsudon | Weepinbell | ハエとりポケモン | Flycatcher Pokémon |
| 071 | ウツボット | Utsubotto | Utsubot | Victreebel | ハエとりポケモン | Flycatcher Pokémon |
| 072 | メノクラゲ | Menokurage | Menokurage | Tentacool | くらげポケモン | Jellyfish Pokémon |
| 073 | ドククラゲ | Dokukurage | Dokukurage | Tentacruel | くらげポケモン | Jellyfish Pokémon |
| 074 | イシツブテ | Ishitsubute | Isitsubute | Geodude | がんせきポケモン | Rock Pokémon |
| 075 | ゴローン | Goroon | Golone | Graveler | がんせきポケモン | Rock Pokémon |
| 076 | ゴローニャ | Goroonya | Golonya | Golem | メガトンポケモン | Megaton Pokémon |
| 077 | ポニータ | Poniita | Ponyta | Ponyta | ひのうまポケモン | Fire Horse Pokémon |
| 078 | ギャロップ | Gyaroppu | Gallop | Rapidash | ひのうまポケモン | Fire Horse Pokémon |
| 079 | ヤドン | Yadon | Yadon | Slowpoke | まぬけポケモン | Dopey Pokémon |
| 080 | ヤドラン | Yadoran | Yadoran | Slowbro | やどかりポケモン | Hermit Crab Pokémon |
| 081 | コイル | Koiru | Coil | Magnemite | じしゃくポケモン | Magnet Pokémon |
| 082 | レアコイル | Reakoiru | Rarecoil | Magneton | じしゃくポケモン | Magnet Pokémon |
| 083 | カモネギ | Kamonegi | Kamonegi | Farfetch'd | かるがもポケモン | Wild Duck Pokémon |
| 084 | ドードー | Doodoo | Dodo | Doduo | ふたごどりポケモン | Twin Bird Pokémon |
| 085 | ドードリオ | Doodorio | Dodorio | Dodrio | みつごどりポケモン | Triple Bird Pokémon |
| 086 | パウワウ | Pauwau | Pawou | Seel | あしかポケモン | Sea Lion Pokémon |
| 087 | ジュゴン | Jugon | Jugon | Dewgong | あしかポケモン | Sea Lion Pokémon |
| 088 | ベトベター | Betobetaa | Betbeter | Grimer | ヘドロポケモン | Sludge Pokémon |
| 089 | ベトベトン | Betobeton | Betbeton | Muk | ヘドロポケモン | Sludge Pokémon |
| 090 | シェルダー | Sherudaa | Shellder | Shellder | ２まいがいポケモン | Bivalve Pokémon |
| 091 | パルシェン | Parushen | Parshen | Cloyster | ２まいがいポケモン | Bivalve Pokémon |
| 092 | ゴース | Goosu | Ghos | Gastly | ガスじょうポケモン | Gas Pokémon |
| 093 | ゴースト | Goosuto | Ghost | Haunter | ガスじょうポケモン | Gas Pokémon |
| 094 | ゲンガー | Gengaa | Gangar | Gengar | シャドーポケモン | Shadow Pokémon |
| 095 | イワーク | Iwaaku | Iwark | Onix | いわへびポケモン | Rock Snake Pokémon |
| 096 | スリープ | Suriipu | Sleepe | Drowzee | さいみんポケモン | Hypnosis Pokémon |
| 097 | スリーパー | Suriipaa | Sleeper | Hypno | さいみんポケモン | Hypnosis Pokémon |
| 098 | クラブ | Kurabu | Crab | Krabby | さわがにポケモン | River Crab Pokémon |
| 099 | キングラー | Kinguraa | Kingler | Kingler | はさみポケモン | Pincer Pokémon |
| 100 | ビリリダマ | Biriridama | Biriridama | Voltorb | ボールポケモン | Ball Pokémon |
| 101 | マルマイン | Marumain | Marumine | Electrode | ボールポケモン | Ball Pokémon |
| 102 | タマタマ | Tamatama | Tamatama | Exeggcute | たまごポケモン | Egg Pokémon |
| 103 | ナッシー | Nasshii | Nassy | Exeggutor | やしのみポケモン | Coconut Pokémon |
| 104 | カラカラ | Karakara | Karakara | Cubone | こどくポケモン | Lonely Pokémon |
| 105 | ガラガラ | Garagara | Garagara | Marowak | ほねずきポケモン | Bone Keeper Pokémon |
| 106 | サワムラー | Sawamuraa | Sawamular | Hitmonlee | キックポケモン | Kicking Pokémon |
| 107 | エビワラー | Ebiwaraa | Ebiwalar | Hitmonchan | パンチポケモン | Punching Pokémon |
| 108 | ベロリンガ | Beroringa | Beroringa | Lickitung | なめまわしポケモン | Licking Pokémon |
| 109 | ドガース | Dogaasu | Dogars | Koffing | どくガスポケモン | Poison Gas Pokémon |
| 110 | マタドガス | Matadogasu | Matadogas | Weezing | どくガスポケモン | Poison Gas Pokémon |
| 111 | サイホーン | Saihoon | Sihorn | Rhyhorn | とげとげポケモン | Spikes Pokémon |
| 112 | サイドン | Saidon | Sidon | Rhydon | ドリルポケモン | Drill Pokémon |
| 113 | ラッキー | Rakkii | Lucky | Chansey | たまごポケモン | Egg Pokémon |
| 114 | モンジャラ | Monjara | Monjara | Tangela | ツルじょうポケモン | Vine Pokémon |
| 115 | ガルーラ | Garuura | Garura | Kangaskhan | おやこポケモン | Parent Pokémon |
| 116 | タッツー | Tattsuu | Tattu | Horsea | ドラゴンポケモン | Dragon Pokémon |
| 117 | シードラ | Shiidora | Seadra | Seadra | ドラゴンポケモン | Dragon Pokémon |
| 118 | トサキント | Tosakinto | Tosakinto | Goldeen | きんぎょポケモン | Goldfish Pokémon |
| 119 | アズマオウ | Azumaou | Azumao | Seaking | きんぎょポケモン | Goldfish Pokémon |
| 120 | ヒトデマン | Hitodeman | Hitodeman | Staryu | ほしがたポケモン | Star Shape Pokémon |
| 121 | スターミー | Sutaamii | Starmie | Starmie | なぞのポケモン | Mysterious Pokémon |
| 122 | バリヤード | Bariyaado | Barrierd | Mr. Mime | バリアーポケモン | Barrier Pokémon |
| 123 | ストライク | Sutoraiku | Strike | Scyther | かまきりポケモン | Mantis Pokémon |
| 124 | ルージュラ | Ruujura | Rougela | Jynx | ひとがたポケモン | Human Shape Pokémon |
| 125 | エレブー | Erebuu | Eleboo | Electabuzz | でんげきポケモン | Electric Pokémon |
| 126 | ブーバー | Buubaa | Boober | Magmar | ひふきポケモン | Spitfire Pokémon |
| 127 | カイロス | Kairosu | Kailios | Pinsir | くわがたポケモン | Stag Beetle Pokémon |
| 128 | ケンタロス | Kentarosu | Kentauros | Tauros | あばれうしポケモン | Wild Bull Pokémon |
| 129 | コイキング | Koikingu | Koiking | Magikarp | さかなポケモン | Fish Pokémon |
| 130 | ギャラドス | Gyaradosu | Gyarados | Gyarados | きょうあくポケモン | Atrocious Pokémon |
| 131 | ラプラス | Rapurasu | Laplace | Lapras | のりものポケモン | Transport Pokémon |
| 132 | メタモン | Metamon | Metamon | Ditto | へんしんポケモン | Transform Pokémon |
| 133 | イーブイ | Iibui | Eievui | Eevee | しんかポケモン | Evolution Pokémon |
| 134 | シャワーズ | Shawaazu | Showers | Vaporeon | あわはきポケモン | Bubble Jet Pokémon |
| 135 | サンダース | Sandaasu | Thunders | Jolteon | かみなりポケモン | Lightning Pokémon |
| 136 | ブースター | Buusutaa | Booster | Flareon | ほのおポケモン | Flame Pokémon |
| 137 | ポリゴン | Porigon | Porygon | Porygon | シージーポケモン (Zero; later games バーチャルポケモン) | Virtual Pokémon |
| 138 | オムナイト | Omunaito | Omnite | Omanyte | うずまきポケモン | Spiral Pokémon |
| 139 | オムスター | Omusutaa | Omstar | Omastar | うずまきポケモン | Spiral Pokémon |
| 140 | カブト | Kabuto | Kabuto | Kabuto | こうらポケモン | Shellfish Pokémon |
| 141 | カブトプス | Kabutopusu | Kabutops | Kabutops | こうらポケモン | Shellfish Pokémon |
| 142 | プテラ | Putera | Ptera | Aerodactyl | かせきポケモン | Fossil Pokémon |
| 143 | カビゴン | Kabigon | Kabigon | Snorlax | いねむりポケモン | Sleeping Pokémon |
| 144 | フリーザー | Furiizaa | Freezer | Articuno | れいとうポケモン | Freeze Pokémon |
| 145 | サンダー | Sandaa | Thunder | Zapdos | でんげきポケモン | Electric Pokémon |
| 146 | ファイヤー | Faiyaa | Fire | Moltres | かえんポケモン | Flame Pokémon |
| 147 | ミニリュウ | Miniryuu | Miniryu | Dratini | ドラゴンポケモン | Dragon Pokémon |
| 148 | ハクリュー | Hakuryuu | Hakuryu | Dragonair | ドラゴンポケモン | Dragon Pokémon |
| 149 | カイリュー | Kairyuu | Kairyu | Dragonite | ドラゴンポケモン | Dragon Pokémon |
| 150 | ミュウツー | Myuutsuu | Mewtwo | Mewtwo | いでんしポケモン | Genetic Pokémon |
| 151 | ミュウ | Myuu | Mew | Mew | しんしゅポケモン | New Species Pokémon |

## Types

Gen 1 has 15 types, and all 15 Japanese names appear in Zero's text. Steel, Dark and Fairy do not exist yet. Note エスパー (Esper) → **Psychic**.

| Japanese | Romanization | English |
|---|---|---|
| ノーマル | Noomaru | Normal |
| かくとう | Kakutou | Fighting |
| ひこう | Hikou | Flying |
| どく | Doku | Poison |
| じめん | Jimen | Ground |
| いわ | Iwa | Rock |
| むし | Mushi | Bug |
| ゴースト | Goosuto | Ghost |
| ほのお | Honoo | Fire |
| みず | Mizu | Water |
| くさ | Kusa | Grass |
| でんき | Denki | Electric |
| エスパー | Esupaa | Psychic |
| こおり | Koori | Ice |
| ドラゴン | Doragon | Dragon |

## Moves

All 165 Gen 1 moves, in internal move-ID order (Gen 1 internal move IDs; ID 0 is "no move").

Types are the Gen 1 types, which Stadium uses. All 165 Japanese names and type assignments match Zero's move tables (Zero ✓).

| ID | Japanese | Romanization | English | RBY spelling | Type |
|---:|---|---|---|---|---|
| 1 | はたく | Hataku | Pound |  | Normal |
| 2 | からてチョップ | Karatechoppu | Karate Chop |  | Normal (Gen 1; later Fighting) |
| 3 | おうふくビンタ | Oufukubinta | Double Slap | DoubleSlap | Normal |
| 4 | れんぞくパンチ | Renzokupanchi | Comet Punch |  | Normal |
| 5 | メガトンパンチ | Megatonpanchi | Mega Punch |  | Normal |
| 6 | ネコにこばん | Nekonikoban | Pay Day |  | Normal |
| 7 | ほのおのパンチ | Honoonopanchi | Fire Punch |  | Fire |
| 8 | れいとうパンチ | Reitoupanchi | Ice Punch |  | Ice |
| 9 | かみなりパンチ | Kaminaripanchi | Thunder Punch | ThunderPunch | Electric |
| 10 | ひっかく | Hikkaku | Scratch |  | Normal |
| 11 | はさむ | Hasamu | Vise Grip | ViceGrip | Normal |
| 12 | ハサミギロチン | Hasamigirochin | Guillotine |  | Normal |
| 13 | かまいたち | Kamaitachi | Razor Wind |  | Normal |
| 14 | つるぎのまい | Tsuruginomai | Swords Dance |  | Normal |
| 15 | いあいぎり | Iaigiri | Cut |  | Normal |
| 16 | かぜおこし | Kazeokoshi | Gust |  | Normal (Gen 1; later Flying) |
| 17 | つばさでうつ | Tsubasadeutsu | Wing Attack |  | Flying |
| 18 | ふきとばし | Fukitobashi | Whirlwind |  | Normal |
| 19 | そらをとぶ | Soraotobu | Fly |  | Flying |
| 20 | しめつける | Shimetsukeru | Bind |  | Normal |
| 21 | たたきつける | Tatakitsukeru | Slam |  | Normal |
| 22 | つるのムチ | Tsurunomuchi | Vine Whip |  | Grass |
| 23 | ふみつけ | Fumitsuke | Stomp |  | Normal |
| 24 | にどげり | Nidogeri | Double Kick |  | Fighting |
| 25 | メガトンキック | Megatonkikku | Mega Kick |  | Normal |
| 26 | とびげり | Tobigeri | Jump Kick |  | Fighting |
| 27 | まわしげり | Mawashigeri | Rolling Kick |  | Fighting |
| 28 | すなかけ | Sunakake | Sand Attack | Sand-Attack | Normal (Gen 1; later Ground) |
| 29 | ずつき | Zutsuki | Headbutt |  | Normal |
| 30 | つのでつく | Tsunodetsuku | Horn Attack |  | Normal |
| 31 | みだれづき | Midarezuki | Fury Attack |  | Normal |
| 32 | つのドリル | Tsunodoriru | Horn Drill |  | Normal |
| 33 | たいあたり | Taiatari | Tackle |  | Normal |
| 34 | のしかかり | Noshikakari | Body Slam |  | Normal |
| 35 | まきつく | Makitsuku | Wrap |  | Normal |
| 36 | とっしん | Tosshin | Take Down |  | Normal |
| 37 | あばれる | Abareru | Thrash |  | Normal |
| 38 | すてみタックル | Sutemitakkuru | Double-Edge |  | Normal |
| 39 | しっぽをふる | Shippoofuru | Tail Whip |  | Normal |
| 40 | どくばり | Dokubari | Poison Sting |  | Poison |
| 41 | ダブルニードル | Daburuniidoru | Twineedle |  | Bug |
| 42 | ミサイルばり | Misairubari | Pin Missile |  | Bug |
| 43 | にらみつける | Niramitsukeru | Leer |  | Normal |
| 44 | かみつく | Kamitsuku | Bite |  | Normal (Gen 1; later Dark) |
| 45 | なきごえ | Nakigoe | Growl |  | Normal |
| 46 | ほえる | Hoeru | Roar |  | Normal |
| 47 | うたう | Utau | Sing |  | Normal |
| 48 | ちょうおんぱ | Chouonpa | Supersonic |  | Normal |
| 49 | ソニックブーム | Sonikkubuumu | Sonic Boom | SonicBoom | Normal |
| 50 | かなしばり | Kanashibari | Disable |  | Normal |
| 51 | ようかいえき | Youkaieki | Acid |  | Poison |
| 52 | ひのこ | Hinoko | Ember |  | Fire |
| 53 | かえんほうしゃ | Kaenhousha | Flamethrower |  | Fire |
| 54 | しろいきり | Shiroikiri | Mist |  | Ice |
| 55 | みずでっぽう | Mizudeppou | Water Gun |  | Water |
| 56 | ハイドロポンプ | Haidoroponpu | Hydro Pump |  | Water |
| 57 | なみのり | Naminori | Surf |  | Water |
| 58 | れいとうビーム | Reitoubiimu | Ice Beam |  | Ice |
| 59 | ふぶき | Fubuki | Blizzard |  | Ice |
| 60 | サイケこうせん | Saikekousen | Psybeam |  | Psychic |
| 61 | バブルこうせん | Baburukousen | Bubble Beam | BubbleBeam | Water |
| 62 | オーロラビーム | Oororabiimu | Aurora Beam |  | Ice |
| 63 | はかいこうせん | Hakaikousen | Hyper Beam |  | Normal |
| 64 | つつく | Tsutsuku | Peck |  | Flying |
| 65 | ドリルくちばし | Dorirukuchibashi | Drill Peck |  | Flying |
| 66 | じごくぐるま | Jigokuguruma | Submission |  | Fighting |
| 67 | けたぐり | Ketaguri | Low Kick |  | Fighting |
| 68 | カウンター | Kauntaa | Counter |  | Fighting |
| 69 | ちきゅうなげ | Chikyuunage | Seismic Toss |  | Fighting |
| 70 | かいりき | Kairiki | Strength |  | Normal |
| 71 | すいとる | Suitoru | Absorb |  | Grass |
| 72 | メガドレイン | Megadorein | Mega Drain |  | Grass |
| 73 | やどりぎのタネ | Yadoriginotane | Leech Seed |  | Grass |
| 74 | せいちょう | Seichou | Growth |  | Normal |
| 75 | はっぱカッター | Happakattaa | Razor Leaf |  | Grass |
| 76 | ソーラービーム | Sooraabiimu | Solar Beam | SolarBeam | Grass |
| 77 | どくのこな | Dokunokona | Poison Powder | PoisonPowder | Poison |
| 78 | しびれごな | Shibiregona | Stun Spore |  | Grass |
| 79 | ねむりごな | Nemurigona | Sleep Powder |  | Grass |
| 80 | はなびらのまい | Hanabiranomai | Petal Dance |  | Grass |
| 81 | いとをはく | Itoohaku | String Shot |  | Bug |
| 82 | りゅうのいかり | Ryuunoikari | Dragon Rage |  | Dragon |
| 83 | ほのおのうず | Honoonouzu | Fire Spin |  | Fire |
| 84 | でんきショック | Denkishokku | Thunder Shock | ThunderShock | Electric |
| 85 | １０まんボルト | 10manboruto | Thunderbolt |  | Electric |
| 86 | でんじは | Denjiha | Thunder Wave |  | Electric |
| 87 | かみなり | Kaminari | Thunder |  | Electric |
| 88 | いわおとし | Iwaotoshi | Rock Throw |  | Rock |
| 89 | じしん | Jishin | Earthquake |  | Ground |
| 90 | じわれ | Jiware | Fissure |  | Ground |
| 91 | あなをほる | Anaohoru | Dig |  | Ground |
| 92 | どくどく | Dokudoku | Toxic |  | Poison |
| 93 | ねんりき | Nenriki | Confusion |  | Psychic |
| 94 | サイコキネシス | Saikokineshisu | Psychic |  | Psychic |
| 95 | さいみんじゅつ | Saiminjutsu | Hypnosis |  | Psychic |
| 96 | ヨガのポーズ | Yoganopoozu | Meditate |  | Psychic |
| 97 | こうそくいどう | Kousokuidou | Agility |  | Psychic |
| 98 | でんこうせっか | Denkousekka | Quick Attack |  | Normal |
| 99 | いかり | Ikari | Rage |  | Normal |
| 100 | テレポート | Terepooto | Teleport |  | Psychic |
| 101 | ナイトヘッド | Naitoheddo | Night Shade |  | Ghost |
| 102 | ものまね | Monomane | Mimic |  | Normal |
| 103 | いやなおと | Iyanaoto | Screech |  | Normal |
| 104 | かげぶんしん | Kagebunshin | Double Team |  | Normal |
| 105 | じこさいせい | Jikosaisei | Recover |  | Normal |
| 106 | かたくなる | Katakunaru | Harden |  | Normal |
| 107 | ちいさくなる | Chiisakunaru | Minimize |  | Normal |
| 108 | えんまく | Enmaku | Smokescreen | SmokeScreen | Normal |
| 109 | あやしいひかり | Ayashiihikari | Confuse Ray |  | Ghost |
| 110 | からにこもる | Karanikomoru | Withdraw |  | Water |
| 111 | まるくなる | Marukunaru | Defense Curl |  | Normal |
| 112 | バリアー | Bariaa | Barrier |  | Psychic |
| 113 | ひかりのかべ | Hikarinokabe | Light Screen |  | Psychic |
| 114 | くろいきり | Kuroikiri | Haze |  | Ice |
| 115 | リフレクター | Rifurekutaa | Reflect |  | Psychic |
| 116 | きあいだめ | Kiaidame | Focus Energy |  | Normal |
| 117 | がまん | Gaman | Bide |  | Normal |
| 118 | ゆびをふる | Yubiofuru | Metronome |  | Normal |
| 119 | オウムがえし | Oumugaeshi | Mirror Move |  | Flying |
| 120 | じばく | Jibaku | Self-Destruct | Selfdestruct | Normal |
| 121 | タマゴばくだん | Tamagobakudan | Egg Bomb |  | Normal |
| 122 | したでなめる | Shitadenameru | Lick |  | Ghost |
| 123 | スモッグ | Sumoggu | Smog |  | Poison |
| 124 | ヘドロこうげき | Hedorokougeki | Sludge |  | Poison |
| 125 | ホネこんぼう | Honekonbou | Bone Club |  | Ground |
| 126 | だいもんじ | Daimonji | Fire Blast |  | Fire |
| 127 | たきのぼり | Takinobori | Waterfall |  | Water |
| 128 | からではさむ | Karadehasamu | Clamp |  | Water |
| 129 | スピードスター | Supiidosutaa | Swift |  | Normal |
| 130 | ロケットずつき | Rokettozutsuki | Skull Bash |  | Normal |
| 131 | とげキャノン | Togekyanon | Spike Cannon |  | Normal |
| 132 | からみつく | Karamitsuku | Constrict |  | Normal |
| 133 | ドわすれ | Dowasure | Amnesia |  | Psychic |
| 134 | スプーンまげ | Supuunmage | Kinesis |  | Psychic |
| 135 | タマゴうみ | Tamagoumi | Soft-Boiled | Softboiled | Normal |
| 136 | とびひざげり | Tobihizageri | High Jump Kick | Hi Jump Kick | Fighting |
| 137 | へびにらみ | Hebinirami | Glare |  | Normal |
| 138 | ゆめくい | Yumekui | Dream Eater |  | Psychic |
| 139 | どくガス | Dokugasu | Poison Gas |  | Poison |
| 140 | たまなげ | Tamanage | Barrage |  | Normal |
| 141 | きゅうけつ | Kyuuketsu | Leech Life |  | Bug |
| 142 | あくまのキッス | Akumanokissu | Lovely Kiss |  | Normal |
| 143 | ゴッドバード | Goddobaado | Sky Attack |  | Flying |
| 144 | へんしん | Henshin | Transform |  | Normal |
| 145 | あわ | Awa | Bubble |  | Water |
| 146 | ピヨピヨパンチ | Piyopiyopanchi | Dizzy Punch |  | Normal |
| 147 | キノコのほうし | Kinokonohoushi | Spore |  | Grass |
| 148 | フラッシュ | Furasshu | Flash |  | Normal |
| 149 | サイコウェーブ | Saikoweebu | Psywave |  | Psychic |
| 150 | はねる | Haneru | Splash |  | Normal |
| 151 | とける | Tokeru | Acid Armor |  | Poison |
| 152 | クラブハンマー | Kurabuhanmaa | Crabhammer |  | Water |
| 153 | だいばくはつ | Daibakuhatsu | Explosion |  | Normal |
| 154 | みだれひっかき | Midarehikkaki | Fury Swipes |  | Normal |
| 155 | ホネブーメラン | Honebuumeran | Bonemerang |  | Ground |
| 156 | ねむる | Nemuru | Rest |  | Psychic |
| 157 | いわなだれ | Iwanadare | Rock Slide |  | Rock |
| 158 | ひっさつまえば | Hissatsumaeba | Hyper Fang |  | Normal |
| 159 | かくばる | Kakubaru | Sharpen |  | Normal |
| 160 | テクスチャー | Tekusuchaa | Conversion |  | Normal |
| 161 | トライアタック | Toraiatakku | Tri Attack |  | Normal |
| 162 | いかりのまえば | Ikarinomaeba | Super Fang |  | Normal |
| 163 | きりさく | Kirisaku | Slash |  | Normal |
| 164 | みがわり | Migawari | Substitute |  | Normal |
| 165 | わるあがき | Waruagaki | Struggle |  | Normal |

## Items

In Gen 1 internal item-index order (decimal and hex). Gaps are unused or glitch slots. TMs/HMs are listed separately below.
All listed Japanese names match Zero's item table (Zero ✓).

| Index | Hex | Japanese | Romanization | English | RBY spelling |
|---:|---|---|---|---|---|
| 1 | 0x01 | マスターボール | Masutaabooru | Master Ball |  |
| 2 | 0x02 | ハイパーボール | Haipaabooru | Ultra Ball |  |
| 3 | 0x03 | スーパーボール | Suupaabooru | Great Ball |  |
| 4 | 0x04 | モンスターボール | Monsutaabooru | Poké Ball |  |
| 5 | 0x05 | タウンマップ | Taunmappu | Town Map |  |
| 6 | 0x06 | じてんしゃ | Jitensha | Bicycle |  |
| 7 | 0x07 | ？？？？？ |  | (unused; Surfboard slot) |  |
| 8 | 0x08 | サファリボール | Safaribooru | Safari Ball |  |
| 9 | 0x09 | ポケモンずかん | Pokemon zukan | Pokédex |  |
| 10 | 0x0A | つきのいし | Tsukinoishi | Moon Stone |  |
| 11 | 0x0B | どくけし | Dokukeshi | Antidote |  |
| 12 | 0x0C | やけどなおし | Yakedonaoshi | Burn Heal |  |
| 13 | 0x0D | こおりなおし | Koorinaoshi | Ice Heal |  |
| 14 | 0x0E | ねむけざまし | Nemukezamashi | Awakening |  |
| 15 | 0x0F | まひなおし | Mahinaoshi | Paralyze Heal |  |
| 16 | 0x10 | かいふくのくすり | Kaifukunokusuri | Full Restore |  |
| 17 | 0x11 | まんたんのくすり | Mantannokusuri | Max Potion |  |
| 18 | 0x12 | すごいキズぐすり | Sugoikizugusuri | Hyper Potion |  |
| 19 | 0x13 | いいキズぐすり | Iikizugusuri | Super Potion |  |
| 20 | 0x14 | キズぐすり | Kizugusuri | Potion |  |
| 21 | 0x15 | グレーバッジ | Guree bajji | Boulder Badge |  |
| 22 | 0x16 | ブルーバッジ | Buruu bajji | Cascade Badge |  |
| 23 | 0x17 | オレンジバッジ | Orenji bajji | Thunder Badge |  |
| 24 | 0x18 | レインボーバッジ | Reinboo bajji | Rainbow Badge |  |
| 25 | 0x19 | ピンクバッジ | Pinku bajji | Soul Badge |  |
| 26 | 0x1A | ゴールドバッジ | Goorudo bajji | Marsh Badge |  |
| 27 | 0x1B | クリムゾンバッジ | Kurimuzon bajji | Volcano Badge |  |
| 28 | 0x1C | グリーンバッジ | Guriin bajji | Earth Badge |  |
| 29 | 0x1D | あなぬけのヒモ | Ananukenohimo | Escape Rope |  |
| 30 | 0x1E | むしよけスプレー | Mushiyokesupuree | Repel |  |
| 31 | 0x1F | ひみつのコハク | Himitsunokohaku | Old Amber |  |
| 32 | 0x20 | ほのおのいし | Honoonoishi | Fire Stone |  |
| 33 | 0x21 | かみなりのいし | Kaminarinoishi | Thunder Stone |  |
| 34 | 0x22 | みずのいし | Mizunoishi | Water Stone |  |
| 35 | 0x23 | マックスアップ | Makkusuappu | HP Up |  |
| 36 | 0x24 | タウリン | Taurin | Protein |  |
| 37 | 0x25 | ブロムヘキシン | Buromuhekishin | Iron |  |
| 38 | 0x26 | インドメタシン | Indometashin | Carbos |  |
| 39 | 0x27 | リゾチウム | Rizochiumu | Calcium |  |
| 40 | 0x28 | ふしぎなアメ | Fushiginaame | Rare Candy |  |
| 41 | 0x29 | こうらのカセキ | Kouranokaseki | Dome Fossil |  |
| 42 | 0x2A | かいのカセキ | Kainokaseki | Helix Fossil |  |
| 43 | 0x2B | ひみつのカギ | Himitsunokagi | Secret Key |  |
| 45 | 0x2D | ひきかえけん | Hikikaeken | Bike Voucher |  |
| 46 | 0x2E | ヨクアタール | Yokuataaru | X Accuracy |  |
| 47 | 0x2F | リーフのいし | Riifunoishi | Leaf Stone |  |
| 48 | 0x30 | カードキー | Kaadokii | Card Key |  |
| 49 | 0x31 | きんのたま | Kinnotama | Nugget |  |
| 51 | 0x33 | ピッピにんぎょう | Pippiningyou | Poké Doll |  |
| 52 | 0x34 | なんでもなおし | Nandemonaoshi | Full Heal |  |
| 53 | 0x35 | げんきのかけら | Genkinokakera | Revive |  |
| 54 | 0x36 | げんきのかたまり | Genkinokatamari | Max Revive |  |
| 55 | 0x37 | エフェクトガード | Efekutogaado | Guard Spec. |  |
| 56 | 0x38 | シルバースプレー | Shirubaasupuree | Super Repel |  |
| 57 | 0x39 | ゴールドスプレー | Goorudosupuree | Max Repel |  |
| 58 | 0x3A | クリティカッター | Kuritikattaa | Dire Hit |  |
| 60 | 0x3C | おいしいみず | Oishiimizu | Fresh Water |  |
| 61 | 0x3D | サイコソーダ | Saikosooda | Soda Pop |  |
| 62 | 0x3E | ミックスオレ | Mikkusuore | Lemonade |  |
| 63 | 0x3F | ふねのチケット | Funenochiketto | S.S. Ticket |  |
| 64 | 0x40 | きんのいれば | Kinnoireba | Gold Teeth |  |
| 65 | 0x41 | プラスパワー | Purasupawaa | X Attack |  |
| 66 | 0x42 | ディフェンダー | Difendaa | X Defense |  |
| 67 | 0x43 | スピーダー | Supiidaa | X Speed |  |
| 68 | 0x44 | スペシャルアップ | Supesharuappu | X Sp. Atk | X Special |
| 69 | 0x45 | コインケース | Koinkeesu | Coin Case |  |
| 70 | 0x46 | おとどけもの | Otodokemono | Parcel | Oak's Parcel |
| 71 | 0x47 | ダウジングマシン | Daujingumashin | Dowsing Machine | Itemfinder |
| 72 | 0x48 | シルフスコープ | Shirufusukoopu | Silph Scope |  |
| 73 | 0x49 | ポケモンのふえ | Pokemonnofue | Poké Flute |  |
| 74 | 0x4A | エレベータのカギ | Erebeetanokagi | Lift Key |  |
| 75 | 0x4B | がくしゅうそうち | Gakushuusouchi | Exp. Share | Exp.All |
| 76 | 0x4C | ボロのつりざお | Boronotsurizao | Old Rod |  |
| 77 | 0x4D | いいつりざお | Iitsurizao | Good Rod |  |
| 78 | 0x4E | すごいつりざお | Sugoitsurizao | Super Rod |  |
| 79 | 0x4F | ポイントアップ | Pointoappu | PP Up |  |
| 80 | 0x50 | ピーピーエイド | Piipiieido | Ether |  |
| 81 | 0x51 | ピーピーリカバー | Piipiirikabaa | Max Ether |  |
| 82 | 0x52 | ピーピーエイダー | Piipiieidaa | Elixir |  |
| 83 | 0x53 | ピーピーマックス | Piipiimakkusu | Max Elixir |  |

Gen 1 renames worth knowing: タウリン is Protein (not Taurine), ブロムヘキシン is Iron, インドメタシン is Carbos,
リゾチウム is Calcium, マックスアップ is HP Up, プラスパワー is X Attack, ディフェンダー is X Defense,
スピーダー is X Speed, スペシャルアップ is X Special, ヨクアタール is X Accuracy, クリティカッター is Dire Hit (クリティカット in later games),
エフェクトガード is Guard Spec., がくしゅうそうち is Exp. All (Exp. Share from Gen 2 on), ダウジングマシン is Itemfinder.

## TMs and HMs

Gen 1 TM contents (Red/Green/Blue/Yellow); all 55 TM/HM move assignments match Zero's table. Zero does not store
55 separate names. It formats them from the templates `わざマシン%02d` and `ひでんマシン%02d` (`Text_GetTmHmName`
in `src/gb_data.c`), so searching the text for `わざマシン０１` finds nothing. Item index = 0xC4 + HM number − 1 for HMs, 0xC9 + TM number − 1 for TMs.

| Machine | Japanese item | Index | Move (JP) | Move (EN) |
|---|---|---|---|---|
| HM01 | ひでんマシン０１ | 0xC4 | いあいぎり | Cut |
| HM02 | ひでんマシン０２ | 0xC5 | そらをとぶ | Fly |
| HM03 | ひでんマシン０３ | 0xC6 | なみのり | Surf |
| HM04 | ひでんマシン０４ | 0xC7 | かいりき | Strength |
| HM05 | ひでんマシン０５ | 0xC8 | フラッシュ | Flash |
| TM01 | わざマシン０１ | 0xC9 | メガトンパンチ | Mega Punch |
| TM02 | わざマシン０２ | 0xCA | かまいたち | Razor Wind |
| TM03 | わざマシン０３ | 0xCB | つるぎのまい | Swords Dance |
| TM04 | わざマシン０４ | 0xCC | ふきとばし | Whirlwind |
| TM05 | わざマシン０５ | 0xCD | メガトンキック | Mega Kick |
| TM06 | わざマシン０６ | 0xCE | どくどく | Toxic |
| TM07 | わざマシン０７ | 0xCF | つのドリル | Horn Drill |
| TM08 | わざマシン０８ | 0xD0 | のしかかり | Body Slam |
| TM09 | わざマシン０９ | 0xD1 | とっしん | Take Down |
| TM10 | わざマシン１０ | 0xD2 | すてみタックル | Double-Edge |
| TM11 | わざマシン１１ | 0xD3 | バブルこうせん | Bubble Beam |
| TM12 | わざマシン１２ | 0xD4 | みずでっぽう | Water Gun |
| TM13 | わざマシン１３ | 0xD5 | れいとうビーム | Ice Beam |
| TM14 | わざマシン１４ | 0xD6 | ふぶき | Blizzard |
| TM15 | わざマシン１５ | 0xD7 | はかいこうせん | Hyper Beam |
| TM16 | わざマシン１６ | 0xD8 | ネコにこばん | Pay Day |
| TM17 | わざマシン１７ | 0xD9 | じごくぐるま | Submission |
| TM18 | わざマシン１８ | 0xDA | カウンター | Counter |
| TM19 | わざマシン１９ | 0xDB | ちきゅうなげ | Seismic Toss |
| TM20 | わざマシン２０ | 0xDC | いかり | Rage |
| TM21 | わざマシン２１ | 0xDD | メガドレイン | Mega Drain |
| TM22 | わざマシン２２ | 0xDE | ソーラービーム | Solar Beam |
| TM23 | わざマシン２３ | 0xDF | りゅうのいかり | Dragon Rage |
| TM24 | わざマシン２４ | 0xE0 | １０まんボルト | Thunderbolt |
| TM25 | わざマシン２５ | 0xE1 | かみなり | Thunder |
| TM26 | わざマシン２６ | 0xE2 | じしん | Earthquake |
| TM27 | わざマシン２７ | 0xE3 | じわれ | Fissure |
| TM28 | わざマシン２８ | 0xE4 | あなをほる | Dig |
| TM29 | わざマシン２９ | 0xE5 | サイコキネシス | Psychic |
| TM30 | わざマシン３０ | 0xE6 | テレポート | Teleport |
| TM31 | わざマシン３１ | 0xE7 | ものまね | Mimic |
| TM32 | わざマシン３２ | 0xE8 | かげぶんしん | Double Team |
| TM33 | わざマシン３３ | 0xE9 | リフレクター | Reflect |
| TM34 | わざマシン３４ | 0xEA | がまん | Bide |
| TM35 | わざマシン３５ | 0xEB | ゆびをふる | Metronome |
| TM36 | わざマシン３６ | 0xEC | じばく | Self-Destruct |
| TM37 | わざマシン３７ | 0xED | タマゴばくだん | Egg Bomb |
| TM38 | わざマシン３８ | 0xEE | だいもんじ | Fire Blast |
| TM39 | わざマシン３９ | 0xEF | スピードスター | Swift |
| TM40 | わざマシン４０ | 0xF0 | ロケットずつき | Skull Bash |
| TM41 | わざマシン４１ | 0xF1 | タマゴうみ | Soft-Boiled |
| TM42 | わざマシン４２ | 0xF2 | ゆめくい | Dream Eater |
| TM43 | わざマシン４３ | 0xF3 | ゴッドバード | Sky Attack |
| TM44 | わざマシン４４ | 0xF4 | ねむる | Rest |
| TM45 | わざマシン４５ | 0xF5 | でんじは | Thunder Wave |
| TM46 | わざマシン４６ | 0xF6 | サイコウェーブ | Psywave |
| TM47 | わざマシン４７ | 0xF7 | だいばくはつ | Explosion |
| TM48 | わざマシン４８ | 0xF8 | いわなだれ | Rock Slide |
| TM49 | わざマシン４９ | 0xF9 | トライアタック | Tri Attack |
| TM50 | わざマシン５０ | 0xFA | みがわり | Substitute |

## Stats and status conditions

| Japanese | Romanization | English | Notes |
|---|---|---|---|
| HP / たいりょく | Tairyoku | HP | |
| こうげき | Kougeki | Attack | |
| ぼうぎょ | Bougyo | Defense | |
| すばやさ | Subayasa | Speed | |
| とくしゅ | Tokushu | Special | Gen 1 has one Special stat (split into Sp. Atk / Sp. Def in Gen 2) |
| レベル / Lv | Reberu | Level | |
| けいけんち | Keikenchi | Exp. Points | |
| いりょく | Iryoku | Power | move base power |
| めいちゅう | Meichuu | Accuracy | |
| PP | — | PP | |
| わざ | Waza | Move | |
| タイプ | Taipu | Type | |
| どく | Doku | Poison (PSN) | |
| もうどく | Moudoku | Badly poisoned | from Toxic |
| まひ | Mahi | Paralysis (PAR) | |
| ねむり | Nemuri | Sleep (SLP) | |
| やけど | Yakedo | Burn (BRN) | |
| こおり | Koori | Freeze (FRZ) | |
| こんらん | Konran | Confusion | |
| ひんし | Hinshi | Fainted (FNT) | |
| ひるみ | Hirumi | Flinch | |
| きゅうしょ | Kyuusho | Critical hit | literally "vital spot" |

## Battle messages and game terms

`(P)` is a Pokémon name, `(M)` a move name.

| Japanese | English |
|---|---|
| たたかう | Fight |
| ポケモン | Pokémon (party menu; RBY: PKMN) |
| どうぐ / アイテム | Item |
| にげる | Run |
| いれかえる | Switch |
| つよさを みる | Summary / Stats |
| (P)の (M)！ | (P) used (M)! |
| こうかは ばつぐんだ！ | It's super effective! |
| こうかは いまひとつの ようだ | It's not very effective... |
| (P)には こうかが ない みたいだ… | It doesn't affect (P)... |
| きゅうしょに あたった！ | A critical hit! |
| いちげき ひっさつ！ | It's a one-hit KO! |
| (P)の こうげきは はずれた！ | (P)'s attack missed! |
| しかし うまく きまらなかった！ | But it failed! |
| (P)は たおれた！ | (P) fainted! |
| いけっ！ (P)！ | Go! (P)! |
| もどれ！ (P)！ | (P), come back! |
| おめでとう！ (P)は (P2)に しんかした！ | Congratulations! Your (P) evolved into (P2)! |
| しんか | Evolution |
| ポケモンずかん / ずかん | Pokédex |
| ボックス | Box (PC storage) |
| あずける / ひきだす / にがす | Deposit / Withdraw / Release |
| つうしん | Link (cable) |
| こうかん | Trade |
| たいせん | Battle (versus) |
| コロシアム / トレードセンター | Colosseum / Trade Center (link rooms) |
| ニックネーム | Nickname |
| おや | OT (original Trainer) |
| IDNo. | ID No. |
| わざマシン / ひでんマシン | TM / HM |
| ひでんわざ | HM move |
| レポート | Save (literally "report") |
| つづきから はじめる | Continue |
| さいしょから はじめる | New Game |
| せっていを かえる | Options |
| でんどういり | Hall of Fame |
| トレーナー | Trainer |
| モンスターボール | Poké Ball |
| ポケモンリーグ | Pokémon League |

## People

| Japanese | Romanization | English | Notes |
|---|---|---|---|
| レッド | Reddo | Red | Player default name |
| グリーン | Guriin | Blue | Rival default name in Japanese; renamed Blue in English |
| オーキドはかせ | Ookido hakase | Professor Oak | |
| ナナミ | Nanami | Daisy | Oak's granddaughter |
| マサキ | Masaki | Bill | |
| フジろうじん | Fuji roujin | Mr. Fuji | |
| サカキ | Sakaki | Giovanni | Rocket boss / Viridian Gym |
| タケシ | Takeshi | Brock | Pewter Gym (Rock) |
| カスミ | Kasumi | Misty | Cerulean Gym (Water) |
| マチス | Machisu | Lt. Surge | Vermilion Gym (Electric) |
| エリカ | Erika | Erika | Celadon Gym (Grass) |
| キョウ | Kyou | Koga | Fuchsia Gym (Poison) |
| ナツメ | Natsume | Sabrina | Saffron Gym (Psychic) |
| カツラ | Katsura | Blaine | Cinnabar Gym (Fire) |
| カンナ | Kanna | Lorelei | Elite Four (Ice) |
| シバ | Shiba | Bruno | Elite Four (Fighting) |
| キクコ | Kikuko | Agatha | Elite Four (Ghost) |
| ワタル | Wataru | Lance | Elite Four (Dragon) |
| ロケットだん | Roketto-dan | Team Rocket | |
| ムサシ / コジロウ | Musashi / Kojirou | Jessie / James | anime and Yellow only |
| ジムリーダー | Jimu riidaa | Gym Leader | title |
| してんのう | Shitennou | Elite Four | title |
| チャンピオン | Chanpion | Champion | title |
| ライバル | Raibaru | Rival | |

## Trainer classes

Series reference list for Gen 1 classes. Zero's Lv. 1–30 Tournament opponents use only the eight classes in the
second table below. The other classes here, including オヤジ and マニア, were not found in Zero's text.

| Japanese | Romanization | English |
|---|---|---|
| むしとりしょうねん | Mushitori shounen | Bug Catcher |
| たんぱんこぞう | Tanpan kozou | Youngster |
| ミニスカート | Minisukaato | Lass |
| ボーイスカウト | Booisukauto | Jr. Trainer♂ |
| ガールスカウト | Gaarusukauto | Jr. Trainer♀ |
| やまおとこ | Yamaotoko | Hiker |
| ぼうそうぞく | Bousouzoku | Biker |
| かいパンやろう | Kaipan yarou | Swimmer |
| つりびと | Tsuribito | Fisherman |
| エリートトレーナー | Eriito toreenaa | Cooltrainer |
| ジェントルマン | Jentoruman | Gentleman |
| スキンヘッズ | Sukinheddzu | Cue Ball |
| どろぼう (Zero full form: かじばどろぼう) | Dorobou (Kajiba dorobou) | Burglar |
| ロッカー | Rokkaa | Rocker |
| ジャグラー | Jaguraa | Juggler |
| もうじゅうつかい | Moujuu tsukai | Tamer |
| とりつかい | Tori tsukai | Bird Keeper |
| からておう | Karate ou | Blackbelt |
| きとうし | Kitoushi | Channeler |
| ちょうのうりょくしゃ | Chounouryokusha | Psychic |
| おねえさん | Oneesan | Beauty |
| りかけいのおとこ | Rikakei no otoko | Super Nerd |
| ギャンブラー | Gyanburaa | Gambler |
| けんきゅういん | Kenkyuuin | Scientist |
| ふなのり | Funanori | Sailor |
| オヤジ | Oyaji | Mr. Fix |
| マニア | Mania | PokéManiac |
| ロケットだんいん | Roketto-dan'in | Rocket (Grunt) |

### Trainer classes in Zero's Lv. 1–30 Tournament

These are the opponent records at `D_82400400` indices 15–22, repeated across the four cup sets. Each record has
a full class field and a short handle. `\n` is a line break in the game's text; leave it out when searching.

| Index | Full field (Zero ✓) | Short handle (Zero ✓) | English |
|---:|---|---|---|
| 15 | むしとり\nしょうねん | むしとり | Bug Catcher |
| 16 | かじばどろぼう | どろぼう | Burglar |
| 17 | とりつかい | とりつかい | Bird Keeper |
| 18 | ガールスカウト | ガール | Jr. Trainer♀ |
| 19 | りかけいの\nおとこ | りかけい | Super Nerd |
| 20 | たんぱんこぞう | たんぱん | Youngster |
| 21 | ボーイスカウト | ボーイ | Jr. Trainer♂ |
| 22 | ミニスカート | ミニスカ | Lass |

## Places

Zero ✓ marks the labels in the Pokédex habitat map (`D_8A12F2A4`, 36 rows, declared in
`src/fragments/fragment018_262620/pokedex_2190D0.c`). The other places are series reference.

| Japanese | Romanization | English | Notes |
|---|---|---|---|
| カントー | Kantoo | Kanto | region (not named in Gen 1 games) |
| マサラタウン | Masara taun | Pallet Town | |
| トキワシティ | Tokiwa shiti | Viridian City | |
| ニビシティ | Nibi shiti | Pewter City | |
| ハナダシティ | Hanada shiti | Cerulean City | |
| クチバシティ | Kuchiba shiti | Vermilion City | |
| シオンタウン | Shion taun | Lavender Town | |
| タマムシシティ | Tamamushi shiti | Celadon City | |
| ヤマブキシティ | Yamabuki shiti | Saffron City | |
| セキチクシティ | Sekichiku shiti | Fuchsia City | |
| グレンタウン | Guren taun | Cinnabar Island | グレンじま in later games |
| セキエイこうげん | Sekiei kougen | Indigo Plateau | |
| ○ばんどうろ | ...-ban douro | Route ○ | Zero ✓, e.g. １ばんどうろ → Route 1 (fullwidth digits) |
| ○ばんすいどう | ...-ban suidou | Route ○ (sea route) | Zero ✓ for Routes 19–21: １９ばんすいどう → Route 19 |
| トキワのもり | Tokiwa no mori | Viridian Forest | Zero ✓ |
| オツキミやま | Otsukimi yama | Mt. Moon | Zero ✓ spelling; おつきみやま in other games |
| イワヤマトンネル | Iwayama tonneru | Rock Tunnel | Zero ✓ |
| ディグダのあな | Diguda no ana | Diglett's Cave | Zero ✓ |
| ちかつうろ | Chika tsuuro | Underground Path | |
| サイクリングロード | Saikuringu roodo | Cycling Road | |
| ポケモンタワー | Pokemon tawaa | Pokémon Tower | Zero ✓ |
| シルフカンパニー | Shirufu kanpanii | Silph Co. | |
| ゲームコーナー | Geemu koonaa | Game Corner | |
| ロケットだんの アジト | Roketto-dan no ajito | Rocket Hideout | |
| タマムシデパート | Tamamushi depaato | Celadon Dept. Store | |
| サファリゾーン | Safari zoon | Safari Zone | Zero ✓ |
| ふたごじま | Futago jima | Seafoam Islands | Zero ✓ |
| ポケモンやしき | Pokemon yashiki | Pokémon Mansion | Zero ✓ |
| むじんはつでんしょ | Mujin hatsudensho | Power Plant | Zero ✓ |
| チャンピオンロード | Chanpion roodo | Victory Road | Zero ✓ |
| ななしのどうくつ | Nanashi no doukutsu | Cerulean Cave | Zero ✓ (habitat map row 35). Literal: "Nameless Cave"; historical English alias: Unknown Dungeon |
| ハナダのどうくつ | Hanada no doukutsu | Cerulean Cave | Later-game name; not Zero's label |
| サントアンヌごう | Santo Annu gou | S.S. Anne | |
| みさきのこや | Misaki no koya | Sea Cottage | Bill's house; not found in Zero's text |
| かくとうどうじょう | Kakutou doujou | Fighting Dojo | |
| ニビかがくはくぶつかん | Nibi kagaku hakubutsukan | Pewter Museum of Science | |
| ポケモンだいすきクラブ | Pokemon daisuki kurabu | Pokémon Fan Club | |
| そだてや | Sodateya | Day Care | |
| ポケモンセンター | Pokemon sentaa | Pokémon Center | |
| フレンドリィショップ | Furendorii shoppu | Poké Mart | |
| ポケモンジム / ジム | Pokemon jimu | Pokémon Gym | |
| オーキド ポケモンけんきゅうじょ | Ookido Pokemon kenkyuujo | Oak's Lab | |

## Stadium modes and features

This section covers Stadium itself and is the least certain part of this file. The English names follow
the names already used in this repo and in the Stadium 1 (international) decomp; the Japanese column should
be filled in from the in-game text as annotation reaches each mode. Entries marked ⚠ are unverified.
The English for Zero ✓ rows is a project rendering, not recovered English text. "Nintendo Cup '97/'98" are
descriptive names; Zero's own labels are the level ranges. Keep the spacing and character width of the
Japanese only where an exact match matters.

| Japanese | Romanization | English | Code / notes |
|---|---|---|---|
| ポケモンスタジアム | Pokemon sutajiamu | Pokémon Stadium | the game; also the main tournament mode ⚠ |
| 64GBパック | Rokujuuyon jii bii pakku | Transfer Pak | reads Red/Green/Blue cartridges |
| コントローラパック | Kontoroora pakku | Controller Pak | |
| ゲームボーイ | Geemu booi | Game Boy | |
| レンタルポケモン | Rentaru pokemon | Rental Pokémon | |
| ポケモンずかん | Pokemon zukan | Pokédex | `pokedex` fragment |
| ミニゲーム | Mini geemu | Mini-game | |
| L　１〜３０での　トーナメント | L 1–30 de no toonamento | Lv. 1–30 Tournament | Zero ✓. Follows the 2nd national tournament's rules (Nintendo Cup '98); 33 usable species. Fullwidth-Ｌ variant also stored |
| L５０〜５５での　トーナメント | L 50–55 de no toonamento | Lv. 50–55 Tournament | Zero ✓. Follows the 1st national tournament's rules (Nintendo Cup '97) and uses its finalists; 40 usable species. See below |
| L　１〜３０　バトル | L 1–30 batoru | Lv. 1–30 Battle | Zero ✓. Free-battle rule label |
| L５０〜５５　バトル | L 50–55 batoru | Lv. 50–55 Battle | Zero ✓. Free-battle rule label |
| モンスターボールカップ | Monsutaa booru kappu | Poké Ball Cup | Zero ✓ |
| スーパーボールカップ | Suupaa booru kappu | Great Ball Cup | Zero ✓ |
| ハイパーボールカップ | Haipaa booru kappu | Ultra Ball Cup | Zero ✓ |
| マスターボールカップ | Masutaa booru kappu | Master Ball Cup | Zero ✓ |
| トーナメント | Toonamento | Tournament | |
| けっしょう / じゅんけっしょう | Kesshou / jun-kesshou | Final / Semifinal | |
| ゆうしょう | Yuushou | Win the tournament / championship | |
| かち / まけ / ひきわけ | Kachi / make / hikiwake | Win / Loss / Draw | |
| じかんぎれ | Jikangire | Time up | |
| じっきょう | Jikkyou | Play-by-play commentary (announcer) | |
| — | — | Cup select | `cup_select` |
| — | — | Battle order select | `battle_order_select` |
| — | — | Lab (PC boxes, items) | `lab_pc_*`, `lab_item` |
| — | — | GB save viewer / GB Pak data | "GB save port" in function notes |


## Nintendo Cup '97 finalists (locked romanizations)

The Lv. 50–55 Tournament uses the teams of the real finalists of the 1st Pokémon League National Tournament
(第1回ポケモンリーグ全国大会, November 1997, later called Nintendo Cup '97). The opponents come from the table
`D_82400400` in `src/fragments/fragment009_175570.c`. `func_82400118` picks indices 0–14, so there are 15
teams. Each `DemoTeamTemplate` has three strings: `unk_04` is the region, `unk_08` is the player's real name
and `unk_0C` is the trainer (OT) name.

**The game's kana is the authority for every reading.** The ROM stores these names only in hiragana (family
name, newline, given name), not in kanji. The kanji come from outside tournament records. They are here
only so a reader can match them up. Several are ambiguous: 美蘭 would normally be read *Miran*, but this
player's name is *Mika*. Never romanize these names from the kanji.

Use the romanizations below verbatim in comments and identifiers. They are Hepburn without macrons, with
long vowels doubled to match the rest of this glossary, and family name first.

Provenance: the index order, regions, kana readings and handles match two independent reads of the ROM
string table (Julius's original research and the 2026-11-11 ROM text audit). The champion's name field
really is just とおる; the ROM does not give "Miyazawa". The kanji come from fan archives (公式戦ヒストリア,
97リーグの猛者達) and one Nintendo results page. The ROM does not confirm them. The strings are not yet in
`src/`; re-check each row against them once they are extracted. The kanji of the three names with variant spellings would
need a 1997–98 print source to settle, but that does not change any romanization.

| Index | Region (`unk_04`) | Real name in game (`unk_08`) | Locked romanization | Kanji (reference only) | Trainer name (`unk_0C`) | Trainer romanization | Risk / why locked |
|---:|---|---|---|---|---|---|---|
| 0 | ほっかいどう (Hokkaido) | かとう かずひと | Katou Kazuhito | 加藤 和人 | マサハル | Masaharu | Medium: 和人 is also read Kazuto, and the trainer name doesn't match the real name |
| 1 | とうほくＡ (Tohoku A) | ゆうき ようじろう | Yuuki Youjirou | 結城 洋次郎 | ようじろう | Youjirou | Low |
| 2 | とうほくＢ (Tohoku B) | たかはし じゅん | Takahashi Jun | 高橋 潤 | じゅん | Jun | Low |
| 3 | ほくりく (Hokuriku) | とおる (given name only) | Tooru | 宮沢 徹 (champion; family name Miyazawa from outside sources only) | おれさま | Oresama | Medium: 徹 is also read Tetsu or Akira. His entry alone has no family name and `unk_00` = 0 rather than 2 |
| 4 | かんとうＡ１ (Kanto A1) | すずき ゆうすけ | Suzuki Yuusuke | 鈴木 雄輔 | ユウスケ | Yuusuke | Low |
| 5 | かんとうＡ２ (Kanto A2) | ふじた みか | Fujita Mika | 藤田 美蘭 | クレア | Clair | **Extreme**: 美蘭 is normally Miran |
| 6 | かんとうＢ (Kanto B) | はやし やすひろ | Hayashi Yasuhiro | 林 泰宏 / 林 康宏 (3rd place; sources differ) | ヤスヒロ | Yasuhiro | Low; the kanji vary but the reading doesn't |
| 7 | ちゅうぶＡ (Chubu A) | やまだ たかひさ | Yamada Takahisa | 山田 高久 | ブルー | Blue | Low–medium: 高久 is also read Takaku |
| 8 | ちゅうぶＢ (Chubu B) | きたがわ やすのり | Kitagawa Yasunori | 北川 恭教 | テンサイ | Tensai ("genius") | **Very high**: 恭教 has many readings (Takayuki, Yoshinori, ...) |
| 9 | かんさい (Kansai) | にしむら しゅん | Nishimura Shun | 西村 峻 / 西村 俊 (runner-up; sources differ) | にっしん | Nisshin | Low–medium: 峻 is also read Takashi |
| 10 | ちゅうごくＡ (Chugoku A) | いまい だいすけ | Imai Daisuke | 今井 大介 | ダイスケ | Daisuke | Low |
| 11 | ちゅうごくＢ (Chugoku B) | いわまさ けんじ | Iwamasa Kenji | 岩政 健次 / 岩政 健治 (sources differ) | サトシ | Satoshi | Low; the kanji vary, and the trainer name doesn't match the real name |
| 12 | しこく (Shikoku) | よしい ひろき | Yoshii Hiroki | 吉井 博紀 | ヒロ | Hiro | Medium: 博紀 is also read Hironori |
| 13 | きゅうしゅうＡ (Kyushu A) | よしとみ たいせい | Yoshitomi Taisei | 吉冨 大成 / 吉富 大成 (4th place; sources differ) | タイセイ | Taisei | Medium: 大成 is also read Kazunari. The family name is unvoiced: Yoshitomi, not Yoshidomi |
| 14 | きゅうしゅうＢ (Kyushu B) | ふちわき あきひろ | Fuchiwaki Akihiro | 渕脇 明裕 / 渕脇 昭裕 (sources differ) | アキヒロ | Akihiro | Low; the kanji vary but the reading doesn't |

In the game, `unk_08` puts a newline between the family name and the given name; the table shows it as a space.
Region names are kana in the game. In annotations, use the English form in parentheses. Trainer names are names
the players chose and have no official English form, and only their kana is verified. By project convention,
a katakana loanword is written in its English spelling (クレア → Clair, ブルー → Blue). That spelling is a
choice: クレア could equally be Claire or Clare. Any other name is romanized, not translated
(テンサイ → Tensai). A playable English localization (e.g. サトシ → Ash) is a separate decision. The glosses in
quotes are only there to explain the name.
