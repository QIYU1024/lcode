syntax on
" 语法高亮

autocmd InsertLeave * se nocul
autocmd InsertEnter * se cul
" 用浅色高亮当前行

set smartindent
" 智能对齐

set autoindent
" 自动对齐

set confirm
" 在处理未保存或只读文件的时候，弹出确认

set tabstop=4
" Tab键的宽度

set softtabstop=4
set shiftwidth=4
"  统一缩进为4

set noexpandtab
" 不要用空格代替制表符

set number
" 显示行号
"
set showmatch

set matchtime=5
