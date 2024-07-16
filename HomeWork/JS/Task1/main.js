const bookList = document.getElementById('book-list');
let lastSelectedIndex = null;

bookList.addEventListener('click', (event) => {
    if (event.target.tagName === 'LI') {
        const items = Array.from(bookList.children);
        const index = items.indexOf(event.target);

        if (event.ctrlKey) {
            event.target.classList.toggle('selected');
        } else if (event.shiftKey) {
            if (lastSelectedIndex !== null) {
                const start = Math.min(lastSelectedIndex, index);
                const end = Math.max(lastSelectedIndex, index);
                for (let i = start; i <= end; i++) {
                    items[i].classList.add('selected');
                }
            }
        } else {
            items.forEach(item => item.classList.remove('selected'));
            event.target.classList.add('selected');
        }

        lastSelectedIndex = index;
    }
});
