# cpToGithub.sh

# entire dir tree at  /Users/rk/_PC/usr/Apple/_C/_wrk/free/emsdk-portable

export DIR_TO_COPY_FROM=/Users/rk/_PC/usr/apple/_c/_wrk/free
export DIR_TO_COPY_TO=/Users/rk/github_files


echo "cd $DIR_TO_COPY_FROM"
cd $DIR_TO_COPY_FROM

# person_*
# gvimrc_SAVE*
# *track*
# icon*
# appNav*

FILES_TO_COPY="
cpToGithub.sh
igotostarsDevel_info.txt
igotostarsDevel_emsdkFiles.txt
per_emcc_my2.html
prodtst.html
igotostars_PROD.html
emcc.sh
cfns.sh
jquery-3.3.1.js
save_jquery
save_emcc.js
MAMB_mindmap.m
mkbak
makeprod.sh
namesToReplace.sh
goldCfns.txt
goldclassesinC.txt
goldclassesinjs.txt
goldgblsvar.txt
goldidsinC.txt
goldidsinjs.txt
goldnames.txt
goldparams.txt
goldvarvars.txt
shuffle.sh
OLD.txt
console.c
s.sh
prunehtml.sh
macVimSynHIcategories.txt
gvimrc_SAVE_20200131_HTMLandJS
grphtm.c
incocoa.c
incocoa.h
perdoc.c
perdoc.h
perhtm.c
perhtm.h
futasp.c
futdefs.h
futdoc.c
futdoc.h
futhtm.c
futhtm.h
grpdoc.c
grpdoc.h
mambutil.c
rk.h
rkdebug.c
rkdebug.h
rkdebug_externs.h
rktest.c
rktest.sh
Makefile"


for fil in $FILES_TO_COPY
do
  echo "cp $DIR_TO_COPY_FROM/$fil $DIR_TO_COPY_TO"
  cp -p "$fil" "$DIR_TO_COPY_TO"
  #  -p    Cause cp to preserve the following attributes of each source file
  #  in the copy: modification time, access time, file flags, file mode,
  #  user ID, and group ID, as allowed by permissions.  Access Control
  #  Lists (ACLs) and Extended Attributes (EAs), including resource
  #  forks, will also be preserved.
  #
done  

# put non-emdsk files into cpio
echo  "$FILES_TO_COPY"  |  cpio -o  > $DIR_TO_COPY_TO/non_emsdk.cpio



# end of cpToGithub.sh
