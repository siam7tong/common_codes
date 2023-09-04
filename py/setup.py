from setuptools import setup
from torch.utils.cpp_extension import BuildExtension, CUDAExtension

setup(
    name='retinanet',
    version='0.1',
    description='Fast and accurate single shot object detector',
    author = 'NVIDIA Corporation',
    author_email='fchabert@nvidia.com',
    packages=['retinanet', 'retinanet.backbones'],
    ext_modules=[CUDAExtension('retinanet._C',
        ['csrc/extensions.cpp', 'csrc/engine.cpp', 'csrc/cuda/decode.cu', 'csrc/cuda/nms.cu'],
        extra_compile_args={
            'cxx': ['-std=c++11', '-O2', '-Wall'],
            'nvcc': [
                '-std=c++11', '--expt-extended-lambda', '--use_fast_math', '-Xcompiler', '-Wall',
                '-gencode=arch=compute_60,code=sm_60', '-gencode=arch=compute_61,code=sm_61',
                '-gencode=arch=compute_70,code=sm_70', '-gencode=arch=compute_72,code=sm_72',
                '-gencode=arch=compute_75,code=sm_75', '-gencode=arch=compute_75,code=compute_75'
            ],
        },
        include_dirs=["/media/zl/Data/pkgs/opencv-3.4.7/opencv347/include", "/media/zl/Data/pkgs/TensorRT-5.1.5.0/include"],
        library_dirs=["/media/zl/Data/pkgs/opencv-3.4.7/opencv347/lib", "/media/zl/Data/pkgs/TensorRT-5.1.5.0/lib"],
        libraries=['nvinfer', 'nvinfer_plugin', 'nvonnxparser', 'opencv_core', 'opencv_highgui', 'opencv_imgproc', 'opencv_imgcodecs'])
    ],
    cmdclass={'build_ext': BuildExtension.with_options(no_python_abi_suffix=True)},
    install_requires=[
        'torch>=1.0.0a0',
        'torchvision',
        'apex @ git+https://github.com/NVIDIA/apex',
        'pycocotools @ git+https://github.com/nvidia/cocoapi.git#subdirectory=PythonAPI',
        'pillow==9.3.0',
        'requests',
    ],
    entry_points = {'console_scripts': ['retinanet=retinanet.main:main']}
)
