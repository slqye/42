import sys
import os
import cv2
import random
import numpy as np
import typer

AUGMENTATIONS = [
    "rotation",
    "blur",
    "contrast",
    "scaling",
    "illumination",
    "projective"
]


def compute_rotation(image: np.ndarray, angle: float) -> np.ndarray:
    """
    Compute and return the new rotated image.
    """
    shape: tuple = image.shape[:2]
    center: tuple = (shape[0] // 2, shape[1] // 2)
    matrix: np.ndarray = cv2.getRotationMatrix2D(center, angle, 1)
    return cv2.warpAffine(image, matrix, shape)


def compute_blur(image: np.ndarray, kernel: int) -> np.ndarray:
    """
    Compute and return the new blured image.
    """
    return cv2.GaussianBlur(image, (kernel, kernel), 0)


def compute_contrast(image: np.ndarray, amount: float) -> np.ndarray:
    """
    Compute and return the new contrasted image.
    """
    return cv2.convertScaleAbs(image, alpha=amount, beta=0)


def compute_scale(image: np.ndarray, amount: float) -> np.ndarray:
    """
    Compute and return the new scaled image.
    """
    shape: tuple = image.shape[:2]
    scaled: np.ndarray = cv2.resize(
        image,
        None,
        fx=amount,
        fy=amount,
        interpolation=cv2.INTER_LINEAR
    )
    added_height = (scaled.shape[0] - shape[0]) // 2
    added_width = (scaled.shape[1] - shape[1]) // 2
    return scaled[
        added_height:added_height + shape[0],
        added_width:added_width + shape[1]
    ]


def compute_illumination(image: np.ndarray, amount: float) -> np.ndarray:
    """
    Compute and return the new illuminated image.
    """
    return cv2.convertScaleAbs(image, alpha=1, beta=amount)


def compute_projective(image: np.ndarray, range: float) -> np.ndarray:
    """
    Compute and return the new projected image.
    """
    shape: tuple = image.shape[:2]
    offsets: np.ndarray = np.random.uniform(low=-range, high=range, size=(8,))
    pts1: np.ndarray = np.float32([
        [0, 0],
        [shape[1], 0],
        [0, shape[0]],
        [shape[1], shape[0]]
    ])
    pts2: np.ndarray = np.float32([
        [offsets[0], offsets[1]],
        [shape[1] - offsets[2], offsets[3]],
        [offsets[4], shape[0] - offsets[5]],
        [shape[1] - offsets[6], shape[0] - offsets[7]]
    ])
    matrix: np.ndarray = cv2.getPerspectiveTransform(pts1, pts2)
    return cv2.warpPerspective(image, matrix, shape)


def main(image_path: str) -> None:
    """
    Compute multiple image augmentations.
    """
    image: np.ndarray = None
    collection: list = []

    if not os.path.isfile(image_path):
        raise ValueError("wrong type of argument.")
    image = cv2.imread(image_path)
    collection.append(image)
    collection.append(compute_rotation(image, random.randint(-45, 45)))
    collection.append(compute_blur(image, 15))
    collection.append(compute_contrast(image, 1.5))
    collection.append(compute_scale(image, 1.5))
    collection.append(compute_illumination(image, 50))
    collection.append(compute_projective(image, 25))
    for index, value in enumerate(collection[1:]):
        file_name: str = image_path[
            image_path.rfind("/") + 1:
        ].removesuffix(".JPG")
        cv2.imwrite(f"{file_name}_{AUGMENTATIONS[index]}.JPG", value)
    stack = np.hstack(collection)
    cv2.imshow("Augmentations", stack)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    try:
        typer.run(main)
    except Exception as error:
        print(f"error: {error}", file=sys.stderr)
