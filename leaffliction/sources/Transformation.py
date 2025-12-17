import sys
import os
import numpy as np
import pandas as pd
import cv2
import matplotlib.pyplot as plt
import seaborn as sns
import typer

from plantcv import plantcv as pcv
from tqdm import tqdm


class Transformator:
    """
    Object used to apply transformations on an image.
    """

    def __init__(self, file: str, image: np.ndarray = None) -> None:
        """
        Default init state for the class.
        """
        self._file: str = file
        self._image: np.ndarray = image
        if image is None:
            self._image = pcv.readimage(self._file)[0]
        self.compute = self._Compute(self)

        self._mask: np.ndarray = self.compute.mask()

    def display(self, transformations: list = []) -> None:
        """
        Display a horizontal stack of the image,
        its mask and another image if needed.
        """
        transformations.insert(0, self._image)
        display: np.hstack = np.hstack(transformations)
        cv2.imshow(self._file, display)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    def plot(self, dataframe: pd.DataFrame, xlabel: str, ylabel: str) -> None:
        """
        Plot a dataframe.
        """
        sns.lineplot(data=dataframe, dashes=False)
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)
        plt.tight_layout()
        plt.waitforbuttonpress()
        plt.close()

    class _Compute:
        """
        All image computation operations.
        """

        def __init__(self, parent: "Transformator") -> None:
            """
            Compute init state.
            """
            self._parent = parent

        def mask(self) -> np.ndarray:
            """
            Compute and return a mask of the image.
            """
            hsv = cv2.cvtColor(self._parent._image, cv2.COLOR_BGR2HSV)
            lower = np.array([35, 40, 40])
            upper = np.array([85, 255, 255])
            return cv2.inRange(hsv, lower, upper)

        def gaussian_blur(self) -> np.ndarray:
            """
            Compute and return the image with gaussian blur computed.
            """
            image: np.ndarray = cv2.cvtColor(
                self._parent._mask,
                cv2.COLOR_GRAY2BGR
            )
            return pcv.gaussian_blur(img=image, ksize=(5, 5))

        def masked(self) -> np.ndarray:
            """
            Compute and return the image with the mask computed.
            """
            median: np.ndarray = pcv.median_blur(
                gray_img=self._parent._mask,
                ksize=5
            )
            return pcv.apply_mask(
                img=self._parent._image,
                mask=median,
                mask_color="white"
            )

        def roi_objects(self) -> np.ndarray:
            """
            Compute and return the image with roi objects computed.
            """
            image: np.ndarray = self._parent._image.copy()
            median: np.ndarray = pcv.median_blur(
                gray_img=self._parent._mask,
                ksize=5
            )
            image[median == 255] = [0, 255, 0]
            return image

        def analyze_object(self) -> np.ndarray:
            """
            Compute and return the image analyzed by size and shape.
            """
            labeled_mask, _ = pcv.create_labels(mask=self._parent._mask)
            return pcv.analyze.size(
                img=self._parent._image,
                labeled_mask=labeled_mask
            )

        def pseudolandmarks(self) -> np.ndarray:
            """
            Compute and return the image with pseudolandmarks computed.
            """
            image: np.ndarray = self._parent._image.copy()
            landmarks_x = pcv.homology.x_axis_pseudolandmarks(
                self._parent._image,
                self._parent._mask
            )
            default_color: list = [50, 50, 50]
            for index, landmarks in enumerate(landmarks_x):
                color: list = default_color
                color[index] = 255
                for i in landmarks:
                    landmark = i[0]
                    try:
                        position = (int(landmark[0]), int(landmark[1]))
                    except Exception:
                        return image
                    image = cv2.circle(
                        image,
                        position,
                        radius=5,
                        color=color,
                        thickness=-1
                    )
            return image

        def histogram(self) -> pd.DataFrame:
            """
            Compute and plot the color histogram of the image.
            """
            types: dict = {
                "blue": "blue_frequencies",
                "green": "green_frequencies",
                "red": "red_frequencies",
                "lightness": "lightness_frequencies",
                "green_magenta": "green-magenta_frequencies",
                "blue_yellow": "blue-yellow_frequencies",
                "hue": "hue_frequencies",
                "saturation": "saturation_frequencies",
                "value": "value_frequencies",
            }
            pcv.analyze.color(
                rgb_img=self._parent._image,
                labeled_mask=self._parent._mask,
                n_labels=1,
                colorspaces="all"
            )
            observations: object = pcv.outputs.observations["default_1"]
            data: dict = {
                color: observations[types[color]]["value"]
                for color in types
            }
            data["hue"] = np.pad(
                data["hue"],
                (0, 256 - len(data["hue"])),
                mode="constant"
            )
            dataframe: pd.DataFrame = pd.DataFrame(data).reset_index(drop=True)
            return dataframe.reset_index(drop=True)


def file_input_case(file: str) -> None:
    """
    Compute and display multiple image transformations.
    """
    collection: list = []

    if not os.path.isfile(file):
        raise ValueError("wrong type of argument, a file is expected.")
    image: Transformator = Transformator(file)
    collection.extend([
        image.compute.gaussian_blur(),
        image.compute.masked(),
        image.compute.roi_objects(),
        image.compute.analyze_object(),
        image.compute.pseudolandmarks(),
    ])
    image.display(collection)
    image.plot(
        image.compute.histogram(),
        "Pixel intensity",
        "Proportion of pixels (%)"
    )


def folder_input_case(folder: str, output: str) -> None:
    """
    Compute and save multiple image transformations.
    """
    collection: list = []
    images: list = None
    path: str = None
    new_path: str = None
    index_path: str = None

    if not os.path.isdir(folder) or not os.path.isdir(output):
        raise ValueError("wrong type of argument, a directory is expected.")
    images = [
        x for x in os.listdir(folder)
        if os.path.isfile(os.path.join(folder, x))
    ]
    for image in tqdm(images):
        path = os.path.join(folder, image)
        new_path = os.path.splitext(os.path.join(output, image))[0]
        transformator: Transformator = Transformator(path)
        collection = [
            transformator.compute.gaussian_blur(),
            transformator.compute.masked(),
            transformator.compute.roi_objects(),
            transformator.compute.analyze_object(),
            transformator.compute.pseudolandmarks(),
        ]
        for index, new_image in enumerate(collection):
            index_path = f"{new_path}_{index}.jpg"
            pcv.print_image(new_image, index_path)


def main(src: str, dst: str = None) -> None:
    """
    Compute multiple image augmentations.
    """
    if dst is not None:
        return folder_input_case(src, dst)
    return file_input_case(src)


if __name__ == "__main__":
    try:
        sns.set_theme()
        typer.run(main)
    except Exception as error:
        print(f"error: {error}", file=sys.stderr)
