const images = [
    'image/image1.jpg',
    'image/image2.jpg',
    'image/image3.jpg'
];

let currentIndex = 0;

const galleryImage = document.getElementById('galleryImage');
const prevBtn = document.getElementById('prevBtn');
const nextBtn = document.getElementById('nextBtn');

function updateGallery() {
    galleryImage.src = images[currentIndex];
    prevBtn.disabled = currentIndex === 0;
    nextBtn.disabled = currentIndex === images.length - 1;
}

prevBtn.addEventListener('click', () => {
    if (currentIndex > 0) {
        currentIndex--;
        updateGallery();
    }
});

nextBtn.addEventListener('click', () => {
    if (currentIndex < images.length - 1) {
        currentIndex++;
        updateGallery();
    }
});

updateGallery();