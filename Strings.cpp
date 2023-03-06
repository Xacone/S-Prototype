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
           <body style="font-family:calibri; font-size:17px;">
           <h1 style="text-align:center; font-size:35px;" > Guide de filtrage </h1>

           Le filtrage est une fonctionnalité qui permet de filtrer les paquets capturés selon leur(s) type(s).<br>
           Une fois le filtre appliqué, seuls les paquets correspondants au filtre seront capturés et traités.<br>
           Attention, cette fonctionnalité ne détruit pas les paquets qui ne correspondent pas au filtre, ils ne sont qu'ignorés.<br>
           L'expression du filtre doit être saisie dans la barre en haut de cet onglet.<br>
           <br>
           Si vous souhaitez appliquer le filtre uniquement sur votre machine saisissez votre expression sans arguments, si vous souhaitez que le filtre s'applique sur tous les agents, ajoutez l'argument <b>-slaves-all</b> à la fin de votre expression.
           Si vous souhaitez appliquer le filtre sur un seul agent, saisissez à la fin de votre expression <b>-slave <i>@IP de l'agent</i></b><br>







           </body>
           </html>


           )";
}

QString Alert(QString v) { return (QString)"<div style='background: #ff3f34; color: white;'> (!) " + QString(v); }
QString Warning(QString v) { return (QString)"<div style='background: #f6b93b; color: black;'> (-) " + QString(v); }
QString Info(QString v) { return (QString)"<div style='background: #67B7D1; color: black;'> (+) " + QString(v); }
