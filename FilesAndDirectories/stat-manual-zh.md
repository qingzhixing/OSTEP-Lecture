好的，马上为您翻译成中文并调整为更友好的表达风格：

**stat 命令手册（用户命令）**

**名称**
       stat - 显示文件或文件系统状态

**简介**
       stat [选项]... 文件...

**描述**
       这个命令可以帮助您查看文件或文件系统的详细信息。

       长选项的必选参数对于短选项也是必选的。

       -L, --dereference
              跟随符号链接（查看链接指向的原文件）

       -f, --file-system
              显示文件系统状态而非文件状态

       --cached=MODE
              指定如何使用缓存属性；对远程文件系统特别有用。详见下方的 MODE 说明

       -c, --format=FORMAT
              使用用户指定的格式代替默认格式；每次使用格式后会输出换行符

       --printf=FORMAT
              与 --format 类似，但会解释反斜杠转义符，且不会自动在末尾添加换行符；
              如需换行，请在 FORMAT 中包含 \n

       -t, --terse
              以简洁格式打印信息

       --help 显示此帮助信息并退出

       --version
              显示版本信息并退出

       --cached 的 MODE 参数可以是：always, never, 或 default。
               'always' 表示尽可能使用缓存属性；
               'never' 表示尝试同步获取最新属性；
               'default' 则表示由底层文件系统决定。

**适用于文件的格式序列（未使用 --file-system 时）：**

       %a     八进制表示的权限位（注意 '#' 和 '0' printf 标志）
       %A     人类可读的权限位和文件类型
       %b     分配的块数（参见 %B）
       %B     每个块的大小（以字节为单位）
       %C     SELinux 安全上下文字符串
       %d     十进制设备号 (st_dev)
       %D     十六进制设备号 (st_dev)
       %Hd    十进制主设备号
       %Ld    十进制次设备号
       %f     十六进制原始模式
       %F     文件类型
       %g     所有者的组 ID
       %G     所有者的组名称
       %h     硬链接数量
       %i     inode 编号
       %m     挂载点
       %n     文件名
       %N     带引号的文件名，如果是符号链接则会解引用
       %o     最优 I/O 传输大小提示
       %s     总大小（字节）
       %r     十进制设备类型 (st_rdev)
       %R     十六进制设备类型 (st_rdev)
       %Hr    十进制主设备类型（适用于字符/块设备特殊文件）
       %Lr    十进制次设备类型（适用于字符/块设备特殊文件）
       %t     十六进制主设备类型（适用于字符/块设备特殊文件）
       %T     十六进制次设备类型（适用于字符/块设备特殊文件）
       %u     所有者的用户 ID
       %U     所有者的用户名称
       %w     文件创建时间（人类可读格式）；未知则显示 -
       %W     文件创建时间（自 Epoch 起的秒数）；未知则为 0
       %x     最后访问时间（人类可读）
       %X     最后访问时间（自 Epoch 起的秒数）
       %y     最后数据修改时间（人类可读）
       %Y     最后数据修改时间（自 Epoch 起的秒数）
       %z     最后状态变更时间（人类可读）
       %Z     最后状态变更时间（自 Epoch 起的秒数）

**适用于文件系统的格式序列：**

       %a     非超级用户可用的空闲块数
       %b     文件系统中的总数据块数
       %c     文件系统中的总文件节点数
       %d     文件系统中的空闲文件节点数
       %f     文件系统中的空闲块数
       %i     十六进制文件系统 ID
       %l     文件名的最大长度
       %n     文件名
       %s     块大小（用于快速传输）
       %S     基本块大小（用于块计数）
       %t     十六进制文件系统类型
       %T     人类可读的文件系统类型

**注意：**
   --terse 等价于以下格式：
        %n %s %b %f %u %g %D %i %h %t %T %X %Y %Z %W %o %C

   --terse --file-system 等价于以下格式：
        %n %i %l %t %s %S %b %f %a %c %d

**重要提示：**
       您使用的 Shell 可能自带其版本的 stat 命令，其通常会覆盖此处描述的版本。
       请查阅您 Shell 的文档以了解其支持的选项。

**作者**
       由 Michael Meskes 编写。

**报告错误**
       GNU coreutils 在线帮助：<https://www.gnu.org/software/coreutils/>
       请将任何翻译错误报告至：<https://translationproject.org/team/>

**版权**
       版权所有 © 2023 Free Software Foundation, Inc.
       许可证 GPLv3+: GNU GPL 第 3 版或更新版本 <https://gnu.org/licenses/gpl.html>。
       本软件是自由软件：您可以自由修改和重新分发它。
       在法律允许的范围内，不提供任何担保。

**参见**
       stat(2), statfs(2), statx(2)

       完整文档请访问：<https://www.gnu.org/software/coreutils/stat>
       或在本地通过以下命令查看：info '(coreutils) stat invocation'

GNU coreutils 9.4                                       2025年6月                                                STAT(1)
