GPU=0
CUDNN=0
OPENCV=0
OPENMP=1
DEBUG=0
CAFFE=0
ODLA=1

CROSS_COMPILE ?= riscv64-unknown-linux-gnu-

ARCH= -gencode arch=compute_30,code=sm_30 \
      -gencode arch=compute_35,code=sm_35 \
      -gencode arch=compute_50,code=[sm_50,compute_50] \
      -gencode arch=compute_52,code=[sm_52,compute_52]
#      -gencode arch=compute_20,code=[sm_20,sm_21] \ This one is deprecated?

# This is what I use, uncomment if you know your arch and want to specify
# ARCH= -gencode arch=compute_52,code=compute_52

VPATH=./src/:./examples
ifeq ($(CAFFE), 1)
ifeq ($(ODLA), 1)
$(error Can't build both ODLA and Caffe at the same time)
endif
CAFFELIB=libcaffelayer.so
CAFFEOBJ=obj/caffe_layer_impl.o
ALIB=
else
CAFFELIB=
CAFFEOBJ=
ALIB=libdarknet.a
endif
ifeq ($(ODLA), 1)
ODLALIB=libodlalayer.so
ODLAOBJ=obj/odla_layer_impl.o
ALIB=
else
ODLALIB=
ODLAOBJ=
ALIB=libdarknet.a
endif

SLIB=libdarknet.so
EXEC=darknet
OBJDIR=./obj/

CPP=$(CROSS_COMPILE)g++
CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar
NVCC=nvcc
ARFLAGS=rcs
OPTS=-Ofast
LDFLAGS= -lm -pthread 
COMMON= -Iinclude/ -Isrc/
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC

ifeq ($(OPENMP), 1) 
CFLAGS+= -fopenmp
endif

ifeq ($(DEBUG), 1) 
OPTS=-O0 -g
endif

CFLAGS+=$(OPTS)

ifeq ($(OPENCV), 1) 
COMMON+= -DOPENCV
CFLAGS+= -DOPENCV
LDFLAGS+= `pkg-config --libs opencv` 
COMMON+= `pkg-config --cflags opencv` 
endif

ifeq ($(GPU), 1) 
COMMON+= -DGPU -I/usr/local/cuda/include/
CFLAGS+= -DGPU
LDFLAGS+= -L/usr/local/cuda/lib64 -lcuda -lcudart -lcublas -lcurand
endif

ifeq ($(CUDNN), 1) 
COMMON+= -DCUDNN 
CFLAGS+= -DCUDNN
LDFLAGS+= -lcudnn
endif

OBJ=gemm.o utils.o cuda.o deconvolutional_layer.o convolutional_layer.o list.o image.o activations.o im2col.o col2im.o blas.o crop_layer.o dropout_layer.o maxpool_layer.o softmax_layer.o data.o matrix.o network.o connected_layer.o cost_layer.o parser.o option_list.o detection_layer.o route_layer.o upsample_layer.o box.o normalization_layer.o avgpool_layer.o layer.o local_layer.o shortcut_layer.o logistic_layer.o activation_layer.o rnn_layer.o gru_layer.o crnn_layer.o demo.o batchnorm_layer.o region_layer.o reorg_layer.o tree.o  lstm_layer.o l2norm_layer.o yolo_layer.o odla_layer.o caffe_layer.o split_layer.o upsample_odla_layer.o converter.o converter_layer.o
EXECOBJA=captcha.o lsd.o super.o art.o tag.o cifar.o go.o rnn.o segmenter.o regressor.o classifier.o coco.o yolo.o detector.o nightmare.o darknet.o
ifeq ($(GPU), 1) 
LDFLAGS+= -lstdc++ 
OBJ+=convolutional_kernels.o deconvolutional_kernels.o activation_kernels.o im2col_kernels.o col2im_kernels.o blas_kernels.o crop_layer_kernels.o dropout_layer_kernels.o maxpool_layer_kernels.o avgpool_layer_kernels.o
endif

ifeq ($(CAFFE), 1)
LDFLAGS+= -L/usr/lib -L. -lcaffelayer -lcaffe
LNKDARKNET= -ldarknet
endif

ifeq ($(ODLA), 1)
LDFLAGS+= -L. -lnvdla_runtime
LNKDARKNET= -ldarknet
endif

EXECOBJ = $(addprefix $(OBJDIR), $(EXECOBJA))
OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard src/*.h) Makefile include/darknet.h

all: obj backup results $(ODLALIB) $(CAFFELIB) $(SLIB) $(ALIB) $(EXEC)
#all: obj  results $(SLIB) $(ALIB) $(EXEC)


$(EXEC): $(EXECOBJ) $(ODLALIB) $(CAFFELIB) $(SLIB) $(ALIB)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LNKDARKNET) $(ALIB)

$(ALIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(SLIB): $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@ $(LDFLAGS)

ifeq ($(CAFFE), 1)
$(CAFFEOBJ):
	$(CPP) -I/usr/include -Wall -fPIC -O -c src/caffe_layer_impl.cpp -o obj/caffe_layer_impl.o
$(CAFFELIB): $(CAFFEOBJ)
	$(CPP) -shared obj/caffe_layer_impl.o -o libcaffelayer.so -L/usr/lib -L. -lcaffe
endif

ifeq ($(ODLA), 1)
$(ODLAOBJ): src/odla_layer_impl.cpp
	$(CPP) -Wall -fPIC -O -c src/odla_layer_impl.cpp -o obj/odla_layer_impl.o
$(ODLALIB): $(ODLAOBJ)
	$(CPP) -shared obj/odla_layer_impl.o -o libodlalayer.so -L.  -lnvdla_runtime
endif

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: %.cu $(DEPS)
	$(NVCC) $(ARCH) $(COMMON) --compiler-options "$(CFLAGS)" -c $< -o $@

obj:
	mkdir -p obj
backup:
	mkdir -p backup
results:
	mkdir -p results

.PHONY: clean

clean:
	rm -rf $(ODLAOBJ) $(ODLALIB) $(CAFFEOBJ) $(CAFFELIB) $(OBJS) $(SLIB) $(ALIB) $(EXEC) $(EXECOBJ) $(OBJDIR)/*

