const arrowKeys = ['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight'];

document.addEventListener('keydown', function (event) {
    if (!arrowKeys.includes(event.key)) return;
    event.preventDefault();

    let currentSlide = 0;
    const hashMatch = window.location.hash.match(/^#slide-(\d+)$/);
    if (hashMatch) {
        currentSlide = parseInt(hashMatch[1], 10);
    }

    let nextSlide =
        event.key === 'ArrowUp' || event.key === 'ArrowLeft' ? Math.max(0, currentSlide - 1) :
            event.key === 'ArrowDown' || event.key === 'ArrowRight' ? currentSlide + 1
                : currentSlide;

    let nextAnchor = document.getElementById(`slide-${nextSlide}`);
    if (nextAnchor) {
        nextAnchor.scrollIntoView({ behavior: 'smooth' });
        history.pushState(null, '', `#slide-${nextSlide}`);
    }
});
