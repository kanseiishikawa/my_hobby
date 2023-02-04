補完スクリプト置き場所  
```
/usr/local/share/zsh/site-functions/_ssh-multi
```

.zshrcに記載  
```
autoload -Uz _ssh-multi && _ssh-multi
unfunction _ssh-multi && autoload -U _ssh-multi
```
