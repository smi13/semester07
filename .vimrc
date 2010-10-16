" REQUIRED. This makes vim invoke Latex-Suite when you open a tex file.
filetype plugin on

" IMPORTANT: win32 users will need to have 'shellslash' set so that latex
" can be called correctly.
set shellslash

set expandtab
set shiftwidth=3
set tabstop=3 

set autoindent
set cindent

" IMPORTANT: grep will sometimes skip displaying the file name if you
" search in a singe file. This will confuse Latex-Suite. Set your grep
" program to always generate a file-name.
set grepprg=grep\ -nH\ $*

" OPTIONAL: This enables automatic indentation as you type.
filetype indent on

" OPTIONAL: Starting with Vim 1, the filetype of empty .tex files defaults to
" 'plaintex' instead of 'tex', which results in vim-latex not being loaded.
" The following changes the default filetype back to 'tex':
let g:tex_flavor='latex'

set number
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [ASCII=\%03.3b]\ [HEX=\%02.2B]\ [POS=%04l,%04v][%p%%]\ [LEN=%L] 
set laststatus=2

" map <C-b> :w<CR>:!make clean<CR>:!make <CR>
" map <C-y> :!./liscur &<CR>
" map <C-k> :!cp src/* /home/fzentsev/iplinux-bootstrap-0.2.3/chroot-dir/build/liscur/src/ <CR>
map <C-p> :w<CR>:!pdflatex %<CR> 
map <C-s> :w<CR>
map <F7> :make<CR>

" map <C-Space> :call g:KLS.StoreCurrentInputSource()<CR> 
" map <C-PageDown> :let g:kls_currentInputSourceIndex<CR> 

colors wombat

if has("gui_running")
 set gfn=Consolas\ Regular\ 12
 set guioptions-=T " Disable toolbar, menu bar, scroll bars
 set guioptions-=r
 set guioptions-=R
 set guioptions-=F
endif

let lua_version = 5
let lua_subvsersion = 1

syntax on
