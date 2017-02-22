set nocompatible              " be iMproved, required
filetype off                  " required 
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'vim-airline/vim-airline-themes'
"Plugin 'davidhalter/jedi-vim'
Plugin 'vim-airline/vim-airline'
Plugin 'scrooloose/nerdtree'
Plugin 'tmhedberg/SimpylFold'
Plugin 'Valloric/YouCompleteMe' "安装完后，到~/.vim/bundle/YouCompleteMe/目录下运行install.py文件，注意依赖
Plugin 'nvie/vim-flake8'
Plugin 'altercation/vim-colors-solarized'
Plugin 'tomasr/molokai'
Plugin 'vim-latex/vim-latex'
Plugin 'crusoexia/vim-monokai'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line

set nowrap
set nu
set expandtab
set tabstop=4
set softtabstop=4
set shiftwidth=4
set encoding=utf-8
autocmd FileType tex setlocal spell spelllang=en_us,cjk

" enable folding with the spacebar
nnoremap <space> za
nnoremap <c-r> zR
let g:SimpylFold_docstring_preview=1

let python_highlight_all=1
syntax on

set t_Co=256
if has('gui_running')
	set background=dark
	colorscheme solarized
else
	set background=dark
	colorscheme molokai
endif

"vim-latex
set grepprg=grep\ -nH\ $*
let g:tex_flavor='latex'
set iskeyword+=:
autocmd BufEnter *.tex set sw=4

"airline
set laststatus=2
let g:airline_theme='solarized'

"NERDTree
map <C-n> :NERDTreeToggle<CR> " binding Ctrl+n as nerdtree toggle key
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif "if only nerdtree window exist, then exit
let g:NERDTreeDirArrowExpandable = '+'
let g:NERDTreeDirArrowCollapsible = '-'

