# changeRDPPortC

This software is a maintenance tool for Windows Remote Desktop Server.

After changing the RDP port number in the registry to the argument value, Windows is restarted. Use with caution.

One effective security measure when maintaining a Windows server via Remote Desktop is to specify the IP addresses that are allowed to connect[Firewall - rdp port properties - scope - remote - IP address]. This setting prevents attacks from unspecified sources and eliminates the load on the server.

However, this method causes the problem of being unable to connect if the IP address of the connecting side changes.

This software resolves that issue. If multiple IP addresses are registered in the scope, this software is not necessary, but please consider it as a precautionary measure.

Basic and C# versions are also available.

�{�\�t�g�́AWindows�����[�g�f�X�N�g�b�v�T�[�o�[�ێ�c�[���ł��B
���W�X�g����rdp�|�[�g�ԍ��������l�ɕύX��AWindows���ċN�����Ă��܂��B�g�p�͒��ӂ��Ă��������B

�����[�g�f�X�N�g�b�v��Windows�T�[�o�[��ێ炷��ꍇ�̗L���ȃZ�L�����e�B�΍�Ƃ��Đڑ���������IP�A�h���X���w�肷����@������܂�[�t�@�C���[�E�H�[�� - rdp�|�[�g�̃v���p�e�B - �X�R�[�v - �����[�gIP�A�h���X]�B���̐ݒ�́A�s���葽������̃A�^�b�N��h�䂵�A���T�[�o�[�̕��ׂ𖳂����܂��B

�������A���̕��@�́A�ڑ����鑤��IP�A�h���X���ς�����ꍇ�ɐڑ��ł��Ȃ��Ȃ�����N�����܂��B
���̃\�t�g�́A���̖����������܂��B�X�R�[�v�ɕ�����IP�A�h���X��o�^���Ă���ꍇ�́A�{�\�t�g�͕s�v�ł����\���΍�Ƃ��Č������Ă��������B

Basic�ł�C#�ł����J���Ă��܂��B


# Requirement

Visual Studio 2022

Please use it on a Windows machine where PHP is running. PHP is being used to remotely launch this software.
.net framework 4.8 is specified, so please change it as appropriate.

php�����삵�Ă���Windows��Ŏg�p���Ă��������B���u�Ŗ{�\�t�g���N�������邽��php���g�p���Ă��܂��B
.net framework4.8���w�肵�Ă���̂œK�X�ύX���Ă��������B  

# Setup

The following operations are strictly prohibited on operational servers. Remote operations are also prohibited as the connection may be lost.
Please do so at your own risk.

�ȉ��̑���́A�^�p���̃T�[�o�[�ł͌��ւł��B�܂��ڑ����؂��̂ŉ��u�ł̑�������ւł��B
���ȐӔC�ł��肢���܂��B

1. Preparation. �����B

We will decide on two numbers: the default port and the backup port.
The default port for rdp is 3389, but we will change this just to be safe. In what follows, we will **assume** that the default is **50001** and the backup is **50002**.
Check the IP address of the connecting side.

����|�[�g�Ɨ\���|�[�g��2�̔ԍ������߂܂��B
rdp�̊���|�[�g�́A3389�ł����O�̂��߂�����ς��܂��B�ȉ��A�����**50001**�A�\����**50002**��**����**���܂��B
�ڑ����鑤��IP�A�h���X�𒲂ׂĂ��������B

2.Firewall settings. �t�@�C���[�E�H�[���ݒ�

In the firewall settings, close 3389 and add and open the two ports **50001** and **50002**.

�t�@�C���[�E�H�[���̐ݒ��3389�����**50001**��**50002**��2��ǉ����J�����܂��B

![changeRDPPort10](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort10.jpg)

Add the IP address to connect to the default scope of **50001**. The configuration for **50002** is not necessary.

�����**50001**�̃X�R�[�v�ɐڑ�����IP�A�h���X��ǉ����Ă��������B**50002**�̐ݒ�͕s�v�ł��B

![changeRDPPort1](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort1.jpg)

3.Add the static IP masquerade for the router to direct ports **50001** and **50002** to the server.
Please read the manual of your router.

���[�^�[�̐ÓIIP�}�X�J���[�h��**50001**��**50002**��2���T�[�o�[�Ɍ������悤�ǉ��o�^���Ă��������B
�ݒ�́A���g���̃��[�^�[�̐�������ǂ�ł��������B

4.Change the rdp port in the registry to **50001** and reboot.

���W�X�g����rdp�|�[�g��**50001**�ɕύX���čċN�����܂��B

[HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Terminal Server\WinStations\RDP-Tcp]PortNumber�B

![changeRDPPort2](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort2.jpg)

You will now be able to connect to the remote desktop using port **50001**.

�ȏ�ŐV����**50001**���g�p���ă����[�g�f�X�N�g�b�v�ڑ����\�ɂȂ�܂��B

![changeRDPPort3](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort3.jpg)

5.Place this software in any folder. �{�\�t�g��C�ӂ̃t�H���_�ɔz�u���܂��B

If Windows is under UAC management, a dialog will appear when you run it. If you cannot enter it remotely, that's the end of it.
Configure the task scheduler to run this software in order to avoid displaying the UAC confirmation dialog.

Windows��UAC�Ǘ����ł́A���s���Ƀ_�C�A���O���o�܂��B���u�Œ��ɓ���Ȃ��ꍇ�́A����ŃW�G���h�ł��B
UAC�m�F�_�C�A���O���o���Ȃ����߂Ƀ^�X�N�X�P�W���[���ɖ{�\�t�g�����s������ݒ�����܂��B

6.Add a task in Task Scheduler in Administrative Tools.
If you are in an environment where the UAC confirmation dialog does not appear, this setting is not necessary. Please run the EXE directly from php.

�Ǘ��c�[���̃^�X�N�X�P�W���[���Ń^�X�N��ǉ����܂��BUAC�m�F�_�C�A���O���o�Ȃ����Ȃ�΂��̐ݒ�͕K�v����܂���B����php����EXE�����s���Ă��������B

![changeRDPPort4](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort4.jpg)


![changeRDPPort5](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort5.jpg)

Set the path of this software. Use the backup port as an argument. Enter the same path in the start option.

�{�\�t�g�̃p�X��ݒ肵�܂��B�\���|�[�g�������ɂ��܂��B�J�n�I�v�V�����ɓ����p�X����͂��܂��B

![changeRDPPort6](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPortC6.jpg)

In the General tab, enter an arbitrary name and check the boxes as shown.

�S�ʃ^�u�ŔC�ӂ̖��̂���͂��}�̒ʂ�Ƀ`�F�b�N���܂��B

![changeRDPPort7](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort7.jpg)

Enter the administrator password and click OK.

OK�{�^���ŊǗ��҃p�X���[�h����͂��܂��B

![changeRDPPort8](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort8.jpg)

The task scheduler is now ready.

�ȏ�Ń^�X�N�X�P�W���[���̏��������ł��B

7.Create a shortcut for this software and change the link destination in the properties to Task Scheduler.

�{�\�t�g�̃V���[�g�J�b�g���쐬���v���p�e�B�̃����N����^�X�N�X�P�W���[���ɕύX���܂��B

C:\Windows\system32\schtasks.exe /run /tn changerdpport

![changeRDPPort9](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort9.jpg)

You can now run this software without the UAC confirmation dialog.
�ȏ��UAC�m�F�_�C�A���O�����Ŗ{�\�t�g�����s�ł��܂��B

8.Prepare PHP to be launched remotely. ���u�ŋN������php�̏����B

I think there are several ways to remotely launch this software, but in my case, I will introduce the method using PHP because it is simple.
The process is simply to launch the shortcut [7] with exec.
This php will be placed in a public location, so please use a complex file name and location.
Also, although it is not included in this sample, please add a password check process.

�{�\�t�g�����u�ŋN��������@�́A����������Ǝv���܂������̏ꍇ��php���ȒP�Ȃ̂ŏЉ�܂��B
�����́Aexec��[7]�̃V���[�g�J�b�g���N�����邾���ł��B
����php�́A���J����ꏊ�ɒu���̂Ńt�@�C�����Ɣz�u����ꏊ�́A���G�Ȗ��̂ɂ��Ă��������B
�܂��A�T���v���ɂ͂���܂��񂪃p�X���[�h���͏�����ǉ����Ă��������B

	<?PHP
		//Please change the path to match your environment. �p�X�͐ݒu���ɍ��킹�Ă�������
		exec('C:\anydir\changeRDPPort - Shortcut.lnk', $out, $ret);

	?>

# How It Works

If the connecting IP address changes, the firewall scope will prevent access to the default port.

�ڑ����鑤��IP���ς�����ꍇ�Ƀt�@�C���[�E�H�[���̃X�R�[�v�ɂ���Ċ���|�[�g�ɓ���Ȃ��Ȃ�܂��B

1.php start php�Ăяo��

[8] Open the php in a browser. This software will start and change the port to the spare port, then restart the server.
After restarting, the spare port that is not set in the scope will open.

[8]�Őݒu����php���u���E�U�ŊJ���܂��B�{�\�t�g���N�����ė\���|�[�g�ɕύX��T�[�o�[���ċN�����܂��B
�ċN����X�R�[�v�ݒ肵�Ă��Ȃ��\���|�[�g���J���܂��B

2.Connect remote desktop �����[�g�f�X�N�g�b�v�Őڑ�����

Connect via a spare port.

�\���|�[�g�Őڑ����܂��B

![changeRDPPort11](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort11.jpg)

3.Scope the firewall to the new IP.

�t�@�C���[�E�H�[���̃X�R�[�v�ɐV����IP��ݒ肵�܂��B

![changeRDPPort1](http://teamwind.serveblog.net/github/changeRDPPort/changeRDPPort1.jpg)

4.Change the rdp port in the registry back to **50001** and reboot.

���W�X�g����rdp�|�[�g��**50001**�ɖ߂��čċN�����܂��B


That is all. The act of remotely rebooting the server carries risks. Please implement this content after establishing sufficient testing and operational backups.

�ȏ�ł��B���u�ŃT�[�o�[���ċN������s�ׂ́A���X�N�𔺂��܂��B�\���Ȏ����Ɖ^�p�̃o�b�N�A�b�v���m�����������Ŗ{���e�𓱓����Ă��������B

# License

MIT license. Copyright: Teamwind.

# Note

There may be bugs. Use at your own risk. Also, modify the code accordingly.
If you have any requests, please email us. 

�o�O�����邩������܂���B���ȐӔC�ł����p���������B�܂��K�X�R�[�h�ύX���Ă��������B
���v�]�����������܂����烁�[���������B


(Google Translate)

