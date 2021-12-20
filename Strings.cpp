#include <Strings.h>

using namespace std;

QString Welcoming()
{
    QString val;
    val=R"(
    Dans cet onglet sont listés:

            (!) Les erreurs critiques
            (-) Les avertissements
            (+) Les informations
 )";
    return val;
}


QString Welcoming2()
{
    return R"(
                                             .             .            .            .            .
                                       .   .      .    .     .     .    .      .   .      . .  .  -+-

                                         .           .   .        .           .          /         :  .
                                   . .        .  .      /.   .      .    .     .     .  / .      . ' .
                                       .  +       .    /     .          .          .   /      .
                                      .            .  /         .            .        *   .         .     .
                                     .   .      .    *     .     .    .      .   .       .  .
                                         .           .           .           .           .         +  .
                                 . .        .  .       .   .  ,-._  .    .     .     .    .      .   .
                                                             /   |)
                                .   +      .          ___/\_'--._|"...__/\__.._._/~\        .         .   .
                                      .          _.--'      o/o "@                  `--./\          .   .
                                          /~~\/~\           '`  /(___                     `-/~\_            .
                                .      .-'                 /`--'_/   \                          `-/\_
                                 _/\.-'                   /\        , \                           __/~\/\-.__
                                             _____                 _        _       Yazid
                                            / ____|               | |      | |
                                           | (___  _ __  _ __ ___ | |_ ___ | |_ _   _ _ __   ___
                                            \___ \| '_ \| '__/ _ \| __/ _ \| __| | | | '_ \ / _ \
                                            ____) | |_) | | | (_) | || (_) | |_| |_| | |_) |  __/
                                           |_____/| .__/|_|  \___/ \__\___/ \__|\__, | .__/ \___|
                                                  | |                            __/ | |
                                                  |_|                           |___/|_|       v3.0)";
}

QString LearnMore()
{
    return R"(

           <html>
           <body style="font-family:calibri;">
           <h1 style="text-align:center;"> Guide </h1>
           <p> La syntaxe de filtrage de Prototype est la même que celle Winpcap </p>

           <ul>
               <li><a href="#">Utilisation</li>
               <li><a href="#">Pirate</li>
               <li><a href="#">Test</li>
               <li><a href="#">Test</li>
               <li><a href="#">Filtrage</li>
               <li><a href="#">Sauvegardes</li>
           </ul>

           </body>
           </html>


           )";
}

QString Alert(QString v) { return (QString)"<div style='background: #ff3f34; color: white;'> (!) " + QString(v); }
QString Warning(QString v) { return (QString)"<div style='background: #f6b93b; color: black;'> (-) " + QString(v); }
QString Info(QString v) { return (QString)"<div style='background: #67B7D1; color: black;'> (+) " + QString(v); }
