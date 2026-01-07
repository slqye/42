import PIL.Image as pil_image
import numpy as np
import load_image


def main():
    """
    This program show the transpose of a picture.
    """
    image: np.array = None
    zoom: np.array = None
    result: np.array = None

    image = load_image.ft_load("animal.jpeg")
    if (image is None):
        return (None)
    try:
        zoom = np.array(image[100:500, 400:800])
        print("The shape of the image is:", zoom.shape)
        print(zoom)
        result = np.zeros(zoom.shape, dtype=np.uint8)
        for y in range(zoom.shape[0]):
            for x in range(zoom.shape[1]):
                result[x][y] = zoom[y][x]
        print("New shape after transpose:", result.shape)
        print(result)
        result = pil_image.fromarray(result)
        result.show()
    except Exception as e:
        print("Error:", e)
        return (None)


if __name__ == "__main__":
    main()
