# The deploy Docker image build a self-contained Ray instance suitable
# for end users.

FROM ray-project/base-deps
ADD ray.tar /ray
WORKDIR /ray/lib/python
RUN python setup.py install
WORKDIR /ray
